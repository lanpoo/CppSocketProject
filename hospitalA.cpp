#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <map>

using namespace std;
using SockAddr = struct sockaddr_in;
SockAddr addrSched;
SockAddr addrSelf;
double totalCapacity = 0;
double initOccupancy = 0;
double availability = 0;
string availabilityStr = "";
int locaHosp = 0;
int sockfd;
map<pair<int, int>, bool> edgeInfo;
map<int, bool> nodeInfo;
struct node{
    int t;
    double c;
    bool operator < (const node& b) const{
        return c > b.c;
    }
};
vector<node> mp[10000];
map<int ,double> dis;



double dijsktra(int start){
    dis.clear();
    constexpr double INF = 1.0*1E9;
    for(auto x : nodeInfo){
        dis.insert(map<int, double>::value_type(x.first, INF));
    }
    priority_queue<node> q;
    dis[start] = 0;
    q.push({start, 0});
    while(!q.empty()){
        node x = q.top();q.pop();
        if(dis[x.t] < x.c)    continue;
        for(int i = 0; i < mp[x.t].size(); i++){
            node& e = mp[x.t][i];
            if(dis[e.t] > x.c + e.c){
                dis[e.t] = x.c + e.c;
                q.push({e.t, dis[e.t]});
            }
        }
    }
    double ans = 0;
    for(auto x : dis){
        if(x.first == locaHosp){
            ans = x.second;
        }
    }
    return ans;
    
}

void readMp(){
    freopen("map.txt", "r", stdin);
    int s,t;
    double dis;
    while(cin >> s >> t >> dis){
        if(edgeInfo.find({s,t}) == edgeInfo.end()){
            mp[s].push_back({t, dis});
            mp[t].push_back({s, dis});
            edgeInfo.insert(map<pair<int, int>, bool>::value_type(make_pair(s,t), true));
            edgeInfo.insert(map<pair<int, int>, bool>::value_type(make_pair(t,s), true));
        }
        if(nodeInfo.find(s) == nodeInfo.end()){
            nodeInfo.insert(map<int, bool>::value_type(s, true));
        }
        if(nodeInfo.find(t) == nodeInfo.end()){
            nodeInfo.insert(map<int, bool>::value_type(t, true));
        }
    }
}



void bootUp(int argc, char* argv[]){
    readMp();

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        cout << "Error in socket\n";
        return;
    }
    cout << "Hospital A is up and running using UDP on port 30249.\n";
    locaHosp = atoi(argv[1]);
    totalCapacity = static_cast<double>(atof(argv[2]));
    initOccupancy = static_cast<double>(atof(argv[3]));
    cout << "Hospital A has total capacity "<< totalCapacity << " and initial occupancy "<< initOccupancy << ".\n";
    socklen_t len = 0;
    memset(&addrSched, 0, sizeof(addrSched));
    addrSched.sin_family = AF_INET;
    addrSched.sin_port = htons(33249);
    addrSched.sin_addr.s_addr = htonl(INADDR_ANY);

    memset(&addrSelf, 0, sizeof(addrSelf));
    addrSelf.sin_family = AF_INET;
    addrSelf.sin_port = htons(30249);
    addrSelf.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(addrSched);
    if(bind(sockfd, (struct sockaddr*)&addrSelf, sizeof(addrSelf)) < 0){
        cout << "Error in bind\n";
        return;
    }
    string message(string(argv[2]) + "+" + string(argv[3]));
    int sendnum = 0;
    sendnum = sendto(sockfd, message.c_str(), message.size(), 0, 
                     (struct sockaddr*)&addrSched, len);
    if(sendnum < 0){
        cout << "error in sendto\n";
        return;
    }
    
}

void sendToSched(string message){
    socklen_t len = sizeof(addrSched);
    int sendnum = sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&addrSched, len);
    if(sendnum < 0){
        cout << "error in sendto\n";
        exit(1);
    }

}
void recvMessage(){
    char recvbuf[255];
    socklen_t len = sizeof(addrSelf);
    SockAddr cliAddr;
    int recvnum = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)&cliAddr, &len);
    recvbuf[recvnum] = '\0';
    cout << "Hospital A has received input from client at location " << recvbuf << endl;
    int location = atoi(recvbuf);
    bool disValid = true;
    bool avaValid = true;
    string score = "";
    double distance;
    double score_;
    if(nodeInfo.find(location) == nodeInfo.end()){
        disValid = false;
        cout << "Hospital A does not have the location " << location << " in map\n";
    }else{
        if(location == locaHosp){
            disValid = false;
        }else{
            distance = dijsktra(location);
            availability = (totalCapacity - initOccupancy) / totalCapacity;
            cout << "Hospital A has capacity = " << totalCapacity << ",occupation= " 
                 <<initOccupancy << ", availability =" << availability << endl;
            cout << "Hospital A has found the shortest path to client,distance = ";
            if(distance == 0){
                disValid = false;
                cout << "None" << endl;
            }else{
                cout << distance << endl;
            } 
            if(availability < 0 || availability > 1){
                avaValid = false;    
                availabilityStr = "None";
            }
        }
    }
    if(!disValid || !avaValid){
        score = "None+None";
        cout << "Hospital A has the score = None\n";
        sendToSched(score);
        cout << "Hospital A has sent \"location not found\" to the Scheduler" <<endl;
    }else{
        score_ = 1.0 / (distance * (1.1 - availability));
        score = to_string(score_);
        cout << "Hospital A has the score = " << score << endl;
        score = score + "+" + to_string(distance);
        sendToSched(score);
        cout << "Hospital A has sent score = "<< score_ << " and distance = " << distance << "  to the Scheduler" <<endl;
    }
    recvnum = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)&cliAddr, &len);
    if(recvnum < 0){
        cout << "error in recvnum\n";
        exit(1);
    }
    if(recvbuf[0] != '*'){
        initOccupancy = initOccupancy + 1;
        availability = (totalCapacity - initOccupancy) / totalCapacity;
        cout << "Hospital A has been assigned to a client, occupation is updated to "
             << initOccupancy << ", availability is updated to " << availability << endl;;
    }
    
}
int main(int argc, char* argv[]){
    readMp();
    bootUp(argc, argv);
    while(true){
        recvMessage();
    }
    close(sockfd);
    
    return 0;
}
