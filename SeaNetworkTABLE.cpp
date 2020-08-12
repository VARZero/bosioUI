// Sea 프로토콜의 처리를 위해 사용되는 코드

#include "Sea.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread> // 작업 하나당 스레드 하나씩 할당을 하기 위해 사용

void Sea_Method_div(char *N_ID, char *Method){
    // Sea 프로토콜의 메소드에 따른 정의
    if (Method == "SCCREATE"){
        // 스크린 생성
        std::thread* work = new std::thread(ScreenCreateWork);
    }
    else if (Method == "CMCREATE"){
        // 컴포넌트 생성
    }
    else if (Method == "EVENT"+0x00+0x00+0x00){
        // 이벤트
    }
    else if (Method == "SCMODIFY"){
        // 스크린 생성
    }
    else if (Method == "CMMODIFY"){
        // 컴포넌트 생성
    }
    else{
        printf("Unknown Event %s\n", Method);
    }
}

void ScreenCreateWork(){
    ScreenInfo *OneScn = new ScreenInfo("Test",px,py,pz,SeeLR,SeeUD);
}

void Net_Sea_Table(){
    int Sock_Server;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    char recvBuffer[1024];
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
        if ((recvLen = recvfrom(Sock_Server, recvBuffer, 1023, 0, (struct sockaddr*)&clientAddr, &clientLen)) == -1){
            printf("recv error");
        }
        else{
            char N_ID[9], In_Method[9];
            for(short i = 0; i <= 8; ++i){
                N_ID[i] = recvBuffer[i];
            }
            N_ID[8] = '\0';
            for(short i = 0; i <= 8; ++i){
                In_Method[i] = recvBuffer[8+i];
            }
            In_Method[8] = '\0';
            std::string str(recvBuffer);
        }
    }
}