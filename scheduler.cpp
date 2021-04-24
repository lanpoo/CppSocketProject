#include <stdio.h>   
#include <sys/types.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <unistd.h>   
#include <errno.h>   
#include <string.h>   
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <map>
#include <map>
#include <memory>

using std::cout;
using std::endl;
using std::cin;
using std::map;
using std::string;
using std::pair;
using std::make_pair;
using SockAddr = struct sockaddr_in;

struct HosInfo{
    double totalCapacity;
    double initOccupancy;
    uint16_t port;
    HosInfo(double _ca, double _oc, uint16_t _po) :
    totalCapacity(_ca), initOccupancy(_oc), port(_po)
    {

    }
};

SockAddr addrSelfUDP;
SockAddr addrSelfTCP;
SockAddr addrHosA;
SockAddr addrHosB;
SockAddr addrHosC;
int sockfdUDP;
int sockfdTCP;

map<string, std::unique_ptr<HosInfo>> mpInfo;
map<uint16_t, SockAddr> mpAddr;
int cliLocation;




void initAddr(SockAddr& addr, int port){
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
}


void UDPsend(const SockAddr& addr, int port, string message){
    socklen_t len = sizeof(addrSelfUDP);
    int sendnum = 0;
    sendnum = sendto(sockfdUDP, message.c_str(), message.size(), 0, (struct sockaddr*)&addr, len);
    if(sendnum < 0){
        cout << "error in sento\n";
        exit(1);
    }
}

void UDPsendToAll(){
    char recvbuf[255];
    int times = 0;
    socklen_t len = sizeof(addrSelfUDP);
    SockAddr cliAddr;
    string host = "";
    while(times < 3){
        int recvnum = recvfrom(sockfdUDP, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)&cliAddr, &len);
                                                                    //(struct sockaddr*)&cliAddr
        if(recvnum < 0){
            cout << "error in recvfrom\n";
            return;
        }
        
        recvbuf[recvnum] = '\0';
        auto port = ntohs(cliAddr.sin_port);
        if(port == 30249){
            host = "A";
            mpAddr.insert(map<int, SockAddr>::value_type(port, addrHosA));
        }else if(port == 31249){
            host = "B";
            mpAddr.insert(map<int, SockAddr>::value_type(port, addrHosB));
        }else if(port == 32249){
            host = "C";
            mpAddr.insert(map<int, SockAddr>::value_type(port, addrHosC));
        }
        string message(recvbuf);
        int index = 0;
        for(int i = 0; i < message.size(); i++){
            if(message[i] == '+')
                index = i;
        }
        cout << "The Scheduler has received information from Hospital " << host << ":\n";
        cout << "total capacity is " << message.substr(0, index) << " and initial occupancy is " 
            << message.substr(index + 1, message.size() - index - 1) << " \n";
        
        auto ptr = std::make_unique<HosInfo>(stof(message.substr(0, index)), 
                                            stof(message.substr(index + 1, message.size() - index - 1)), 
                                            port);
        mpInfo.insert(map<string, std::unique_ptr<HosInfo>>::value_type(host, std::move(ptr)));
        times++;
    }
}



string getBestHos(const map<string, pair<double, double>> result){
    string host = "";
    double maxScore = -1;
    double minDis = 1e9;
    for(const auto& x : result){
        if(x.second.first > maxScore){
            maxScore = x.second.first;
            host = x.first;
            minDis = x.second.second;
        }else if(x.second.first == maxScore){
            if(x.second.second < minDis){
                maxScore = x.second.first;
                host = x.first;
                minDis = x.second.second;
            }
        }
    }
    return host;
}
string UDPrecv(int times){
    SockAddr cliAddr;
    socklen_t len = sizeof(cliAddr);
    char recvbuf[255];
    string host = "";
    map<string, pair<double, double>> result;
    while(times--){
        int recvnum = recvfrom(sockfdUDP, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)&cliAddr, &len);
        if(recvnum < 0){
            cout << "error in recvfrom\n";
            exit(1);
        }
        recvbuf[recvnum] = '\0';
        auto port = ntohs(cliAddr.sin_port);
        if(port == 30249){
            host = "A";
        }else if(port == 31249){
            host = "B";
        }else if(port == 32249){
            host = "C";
        }
        int index = 0;
        string message(recvbuf);
        for(int i = 0; i < message.size(); i++){
            if(message[i] == '+'){
                index = i;
            }
        }
        double score;
        double distance;
        try{
            score = stof(message.substr(0, index)); 
            distance = stof(message.substr(index + 1, message.size() - index - 1));
            cout << "The Scheduler has received map information from Hospital "<< host 
                 <<", the score = " << score << " and the distance = " << distance <<endl;
            result.insert(map<string, pair<double, double>>::value_type(host, make_pair(score, distance)));
        }catch(...){
            string score = message.substr(0, index);
            string distance = message.substr(index + 1, message.size() - index - 1);
            cout << "The Scheduler has received map information from Hospital "<< host 
                 <<", the score = " << score << " and the distance = " << distance <<endl;
            
        }
        
    }

    if(result.size() == 0){
        return "*";
    }else{
        return getBestHos(result);
    }
}


void updateHost(string message){
    for(auto& x : mpInfo){
        if(x.first == message){
            x.second->initOccupancy += 1;
        }
    }
}


void TCPinit(){
    sockfdTCP = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfdTCP < 0){
        cout << "Error in socktcp\n";
        return;
    }
    initAddr(addrSelfTCP, 34249);
    if(bind(sockfdTCP, (struct sockaddr*)&addrSelfTCP, sizeof(addrSelfTCP)) == -1){
        cout << "Error in bind\n";
        return;
    }

    if(listen(sockfdTCP, 5) == -1){
        cout << "Error in listen\n";
        return;
    }

    SockAddr cliAddr;
    int sockfdCli;
    socklen_t len = sizeof(cliAddr);
    
    std::thread t(UDPsendToAll);
    t.detach();
    while (true){   
        sockfdCli = accept(sockfdTCP, (struct sockaddr*)&cliAddr, &len);
        if(sockfdCli < 0){
            cout << "Error in accept\n";
            return;
        }
        char recvbuf[255];
        int recvnum = recv(sockfdCli, recvbuf, sizeof(recvbuf), 0);
        if(recvnum < 0){
            cout << "error in recv\n";
            exit(1);
        }
        if(recvnum == 0){
            continue;
        }
        recvbuf[recvnum] = '\0';
        cout << "The Scheduler has received client at location " << recvbuf << " from the client using TCP over port " 
                << ntohs(cliAddr.sin_port) << endl;
        int times = 0;
        for(const auto& x : mpInfo){
            if((x.second->totalCapacity  - x.second->initOccupancy) > 0){
                times++;
                UDPsend(mpAddr.find(x.second->port)->second, x.second->port, string(recvbuf));
            }
        }
        string message = UDPrecv(times);
        send(sockfdCli, message.c_str(), message.size(), 0);
        if(message == "A"){
            UDPsend(addrHosA, addrHosA.sin_port, message);
            UDPsend(addrHosB, addrHosA.sin_port, "*");
            UDPsend(addrHosC, addrHosA.sin_port, "*");
            cout << "The Scheduler has assigned Hospital " << message <<" to the client\n";
            cout << "The Scheduler has sent the result to client using TCP over port "<< ntohs(addrSelfTCP.sin_port) << endl;
            cout << "The Scheduler has sent the result to Hospital " << message 
                 << " using UDP over port " << ntohs(addrSelfUDP.sin_port) << endl;
        }else if(message == "B"){
            UDPsend(addrHosA, addrHosA.sin_port, "*");
            UDPsend(addrHosB, addrHosA.sin_port, message);
            UDPsend(addrHosC, addrHosA.sin_port, "*");
            cout << "The Scheduler has assigned Hospital " << message <<" to the client\n";
            cout << "The Scheduler has sent the result to client using TCP over port "<< ntohs(addrSelfTCP.sin_port) << endl;
            cout << "The Scheduler has sent the result to Hospital " << message 
                 << " using UDP over port " << ntohs(addrSelfUDP.sin_port) << endl;
        }else if(message == "C"){
            UDPsend(addrHosA, addrHosA.sin_port, "*");
            UDPsend(addrHosB, addrHosA.sin_port, "*");
            UDPsend(addrHosC, addrHosA.sin_port, message);
            cout << "The Scheduler has assigned Hospital " << message <<" to the client\n";
            cout << "The Scheduler has sent the result to client using TCP over port "<< ntohs(addrSelfTCP.sin_port) << endl;
            cout << "The Scheduler has sent the result to Hospital " << message 
                 << " using UDP over port " << ntohs(addrSelfUDP.sin_port) << endl;
        }else{
            UDPsend(addrHosA, addrHosA.sin_port, "*");
            UDPsend(addrHosB, addrHosA.sin_port, "*");
            UDPsend(addrHosC, addrHosA.sin_port, "*");
            cout << "The Scheduler has assigned Hospital " << message <<"(no result) to the client\n";
            cout << "The Scheduler has sent the result to client using TCP over port "<< ntohs(addrSelfTCP.sin_port) << endl;
            cout << "The Scheduler has sent the result to Hospital " << message 
                 << "(no result) using UDP over port " << ntohs(addrSelfUDP.sin_port) << endl;
        }
        updateHost(message);
    }
    
    
    
    
}


void UDPinit(){
    sockfdUDP = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfdUDP < 0){
        cout << "Error in sock\n";
        return;
    }
    initAddr(addrSelfUDP, 33249);
    initAddr(addrHosA, 30249);
    initAddr(addrHosB, 31249);
    initAddr(addrHosC, 32249);
    

    if(bind(sockfdUDP, (struct sockaddr*)&addrSelfUDP, sizeof(addrSelfUDP)) < 0){
        cout << "Error in bind\n";
        return;
    }
    cout << "The Scheduler is up and running.\n";
    
    
    
}
int main(){
    std::thread threadTCP(TCPinit);
    UDPinit();
    threadTCP.join();
    close(sockfdUDP);
    close(sockfdTCP);
    return 0;
}