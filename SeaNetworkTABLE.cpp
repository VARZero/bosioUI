// Sea 프로토콜의 처리를 위해 사용되는 코드

#include "Sea.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread> // 스크린 하나당 스레드 하나씩 할당을 하기 위해 사용

std::map <int, std::thread*> OneScn_OneThd; // 스크린 하나당 스레드 하나 할당한거 map

void Sea_Method_div(char *N_ID, char *Method){
    // Sea 프로토콜의 메소드에 따른 정의
    
}

void Net_Sea_Table(){
    int Sock_Server;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    char recvBuffer[8196];
    unsigned int clientLen;
    int recvLen;

    if(Sock_Server = socket(AF_INET, SOCK_DGRAM, 0) == -1){
        printf("Socket Error");
        return;
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htonl(2117);

    if (bind(Sock_Server, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){
        printf("Bind fail");
        return;
    }

    while(1){
        clientLen = sizeof(clientAddr);
        if ((recvLen = recvfrom(Sock_Server, recvBuffer, 8195, 0, (struct sockaddr*)&clientAddr, &clientLen)) == -1){
            printf("recv error");
        }
        else{
            
        }
    }
}