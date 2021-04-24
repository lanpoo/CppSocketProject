#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

using SockAddr = struct sockaddr_in;
SockAddr addrSched;
int sockfd;
int cliLoca;

void init(int argv, char* argc[]){
    cliLoca = atoi(argc[1]);

    cout << "The client is up and running\n";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        cout << "Error in socket\n";
        return;
    }
    addrSched.sin_family = AF_INET;
    addrSched.sin_port = htons(34249);
    addrSched.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd, (struct sockaddr*)&addrSched, sizeof(addrSched)) < 0){
        cout << "Error in connect\n";
        return;
    }
    send(sockfd, argc[1], strlen(argc[1]), 0);
    cout << "The client has sent query to Scheduler using TCP: client location " << cliLoca << endl;
}

void TCPrecv(){
    char recvbuf[255];
    socklen_t len = sizeof(addrSched);
    int recvnum = recv(sockfd, recvbuf, sizeof(recvbuf), 0);
    if(recvnum < 0){
        cout << "error in recv\n";
        exit(1);
    }
    recvbuf[recvnum] = '\0';
    if(recvbuf[0] == '*'){
        cout << "Score = None, No assignment\n";
    }else{
        cout << "The client has received results from the Scheduler: assigned to Hospital " 
             << recvbuf << endl;
    }
}

int main(int argv, char* argc[]){
    init(argv, argc);
    TCPrecv();
    close(sockfd);
    return 0;
}