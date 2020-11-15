// Sea 프로토콜의 처리를 위해 사용되는 코드

#include "Sea.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread> // 작업 하나당 스레드 하나씩 할당을 하기 위해 사용
// thread가 map과 충돌;;

//map <int, map<std::string, std::string>> SeaNetworkID; // 데이터 재검증을 위해 저장하는 map

int Sock_Server; // 전송용 소켓
short i; // 임시변수
std::mutex Mut;

// 데이터에서 해당 타입의 변수로 변환시켜 주는 함수
std::string DataToString(std::string inData,std::string MethodName){
    size_t tempstart, tempend;
    tempstart = inData.find(MethodName+':');
    tempend = inData.find('\n',tempstart + MethodName.size() + 2);
    return inData.substr(tempstart + MethodName.size() + 2, tempend - tempstart - MethodName.size() - 2);
}
int DataToInt(std::string inData,std::string MethodName){
    std::string temptxt;
    size_t tempstart, tempend;
    tempstart = inData.find(MethodName+':');
    tempend = inData.find('\n',tempstart + MethodName.size() + 2);
    temptxt = inData.substr(tempstart + MethodName.size() + 2, tempend - tempstart - MethodName.size() - 2);
    return stoi(temptxt);
}
float DataToFloat(std::string inData,std::string MethodName){
    std::string temptxt;
    size_t tempstart, tempend;
    tempstart = inData.find(MethodName+':');
    tempend = inData.find('\n',tempstart + MethodName.size() + 2);
    temptxt = inData.substr(tempstart + MethodName.size() + 2, tempend - tempstart - MethodName.size() - 2);
    return stof(temptxt);
}

// 메소드에 따른 함수
void ScreenCreateWork(std::string Data, char* network_ID, struct sockaddr_in cliAddr){
    int Sid;
    std::string SName;
    float Sx, Sy, Sz, Sh, Sw, ScrLR, ScrUD;
    // Name 가져오기
    SName = DataToString(Data, "name");
    // 위치 가져오기 x, y, z
    Sx = DataToFloat(Data, "X");
    Sy = DataToFloat(Data, "Y");
    Sz = DataToFloat(Data, "Z");
    // 높, 너비 가져오기
    Sh = DataToFloat(Data, "Height");
    Sw = DataToFloat(Data, "Width");
    // 각도 가져오기 AngleLR, AngleUD
    ScrLR = DataToFloat(Data, "AngleLR");
    ScrUD = DataToFloat(Data, "AngleUD");

    cout << SName << endl;
    ScreenInfo *OneScn = new ScreenInfo(SName, Sx, Sy, Sz, Sh, Sw, ScrLR, ScrUD);
    // 생성된 스크린 아이디 전송
    Sid = OneScn->Output_ScreenID();
    char* SidC;
    sprintf(SidC,"%d",Sid);
    char *sendBuf = { *network_ID + (char *) "SREVERSEScreenID:" + *SidC }; // 수정좀 하기
    while(sendto(Sock_Server, sendBuf, sizeof(sendBuf), 0, (struct sockaddr*)&cliAddr, sizeof(cliAddr)) != sizeof(sendBuf)){
        printf("error! I can't send Screen ID!");
    }
}

void ComponentsCreateWork(std::string Data, char* network_ID, struct sockaddr_in cliAddr){
    int Sid, Cid;
    std::string Cname;
    float Cx, Cy, Cw, Ch, Cd;  
    // 스크린 아이디 가져오기
    Sid = DataToInt(Data, "ScreenID");
    Mut.lock();
    ScreenInfo* AddComp_Screen = ScreenList[Sid];
    // 컴포넌트 이름 가져오기
    Cname = DataToString(Data, "CompName");
    // 세부사항 가져오기
    Cx = DataToFloat(Data, "X");
    Cy = DataToFloat(Data, "Y");
    Cw = DataToFloat(Data, "Width");
    Ch = DataToFloat(Data, "Height");
    Cd = DataToFloat(Data, "Depth");

    // 정보 취합해서 넣기
    AddComp_Screen->Add_Components(Cx, Cy, Cw, Ch, Cd, Cname, &Cid);
    Mut.unlock();
    // 생성된 컴포넌트 아이디 돌려주기
    char* CidC;
    sprintf(CidC, "%d", Cid);
    char *sendBuf = { *network_ID + (char *) "SREVERSEComponID: " + *CidC }; // 수정좀 하기
    while(sendto(Sock_Server, sendBuf, sizeof(sendBuf), 0, (struct sockaddr*)&cliAddr, sizeof(cliAddr)) != sizeof(sendBuf)){
        printf("error! I can't send Components ID!");
    }
}

void ComponentsEventWork(std::string Data, char* network_ID, struct sockaddr_in cliAddr){
    // 이벤트 전달
    int Sid, Cid; // 스크린 아이디, 컴포넌트 아이디
    std::string Event;
    Sid = DataToInt(Data, "ScreenID");
    Cid = DataToInt(Data, "ComponentsID");
    Event = DataToString(Data, "Event");
    
}

void ScreenMotifyWork(std::string Data){
    // 스크린 이름, 사이즈 수정
}

void ComponentsMotifyWork(std::string Data){
    // 컴포넌트 내용물, 사이즈 수정
    int Sid = DataToInt(Data, "ScreenID"), Cid = DataToInt(Data, "ComponentsID");
    std::string WorkMeth = DataToString(Data, "Motify");
    if (WorkMeth == "Size"){
        // 사이즈 변경
    }
    else if (WorkMeth == "Points"){
        // 내용물 (캔버스)변경
        int startX = DataToInt(Data, "startX");
        int startY = DataToInt(Data, "startY");
        int length = DataToInt(Data, "Length");
        std::string ColorDatas = DataToString(Data, "Colors");
        Mut.lock();
        ScreenList[Sid]->Components_List[Cid]->Canvas_Components(startX, startY, length, ColorDatas);
        Mut.unlock();
    }
}

int Sea_Method_div(char *Network_ID, const char *Method, char *Screen_ID, std::string Data, struct sockaddr_in cliAddr){
    // Sea 프로토콜의 메소드에 따른 정의
    //((const char *) Method == "SCCREATE")
    if (strcmp(Method, "SCCREATE") == 0){
        // 스크린 생성
        printf("aa");
        std::thread* work = new std::thread(ScreenCreateWork, Data, std::ref(Network_ID), cliAddr);
        
    }
    else if (strcmp(Method,"CMCREATE") == 0){
        // 컴포넌트 생성
        printf("bb");
        std::thread* work = new std::thread(ComponentsCreateWork, Data, std::ref(Network_ID), cliAddr);
    }
    else if (strcmp(Method, "EVENT"+0x00+0x00+0x00) == 0){
        // 이벤트
        printf("cc");
        //std::thread* work = new std::thread(ComponentsEventWork, Data, std::ref(Network_ID), cliAddr);
    }
    else if (strcmp(Method, "SCMODIFY") == 0){
        // 스크린 수정
        printf("dd");
        //std::thread* work = new std::thread(ScreenMotifyWork, Data);
    }
    else if (strcmp(Method, "CMMODIFY") == 0){
        // 컴포넌트 수정
        printf("ee");
        //std::thread* work = new std::thread(ComponentsMotifyWork, Data);
    }
    else{
        printf("Unknown Event %s\n", Method);
    }
    return 1;
}

void Net_Sea_Table(){
    char recvBuffer[1024]; // 수신용 버퍼
    // 클라이언트 관련 아이디들
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    unsigned int clientLen;
    int Sock_Server = socket(AF_INET, SOCK_DGRAM, 0);
    if(Sock_Server == -1){
        printf("Socket Error");
        return;
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(22117);
    int status = ::bind(Sock_Server, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (status == -1){
        printf("Bind fail");
        return;
    }
    while(1){
        clientLen = sizeof(clientAddr);
        ssize_t recvLen = recvfrom(Sock_Server, recvBuffer, 1023, 0, (struct sockaddr*)&clientAddr, &clientLen);
        if (recvLen == -1){
            printf("recv error");
        }
        else{
            char N_ID[9], In_Method[9], Scr_ID[9];
            for(i = 0; i <= 8; ++i){
                N_ID[i] = recvBuffer[i];
            }
            N_ID[8] = '\0';
            cout << N_ID << endl;
            for(i = 0; i <= 8; ++i){
                In_Method[i] = recvBuffer[8+i];
            }
            In_Method[8] = '\0';
            cout << In_Method << endl;
            for(i = 0; i <= 8; ++i){
                Scr_ID[i] = recvBuffer[16+i];
            }
            Scr_ID[8] = '\0';
            cout << Scr_ID << endl;
            std::string BufData(recvBuffer);
            BufData.erase(0,23);
            if (Sea_Method_div(N_ID, In_Method, Scr_ID, BufData, clientAddr) == 1){
                continue;
            }
        }
    }
}