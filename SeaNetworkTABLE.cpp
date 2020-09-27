// Sea 프로토콜의 처리를 위해 사용되는 코드

#include "Sea.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread> // 작업 하나당 스레드 하나씩 할당을 하기 위해 사용

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

void Sea_Method_div(char *Network_ID, char *Method, std::string Data){
    // Sea 프로토콜의 메소드에 따른 정의
    if (Method == "SCCREATE"){
        // 스크린 생성
        std::thread* work = new std::thread(ScreenCreateWork, Data, *Network_ID);
    }
    else if (Method == "CMCREATE"){
        // 컴포넌트 생성
        std::thread* work = new std::thread(ComponentsCreateWork, Data);
    }
    else if (Method == "EVENT"+0x00+0x00+0x00){
        // 이벤트
        std::thread* work = new std::thread(ComponentsEventWork, Data);
    }
    else if (Method == "SCMODIFY"){
        // 스크린 수정
        std::thread* work = new std::thread(ScreenMotifyWork, Data);
    }
    else if (Method == "CMMODIFY"){
        // 컴포넌트 수정
        std::thread* work = new std::thread(ComponentsMotifyWork, Data);
    }
    else{
        printf("Unknown Event %s\n", Method);
    }
}

// 메소드에 따른 함수
void ScreenCreateWork(std::string Data, char* network_ID){
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

    ScreenInfo *OneScn = new ScreenInfo(SName, Sx, Sy, Sz, Sh, Sw, ScrLR, ScrUD);
    // 생성된 스크린 아이디 전송
    Sid = OneScn->Output_ScreenID();
    char sendBuf[1024] = { *network_ID + 'SREVERSE' + 'ScreenID:' + Sid };
    fgets(sendBuf, 1024, stdin);
}

void ComponentsCreateWork(std::string Data){
    int Sid;
    std::string Cname;
    float Cx, Cy, Cw, Ch, Cd;
    
    // 스크린 아이디 가져오기
    Sid = DataToInt(Data, "ScreenID");
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
    AddComp_Screen->Add_Components(Cx, Cy, Cw, Ch, Cd, Cname);
    
    // 생성된 컴포넌트 아이디 돌려주기
}

void ComponentsEventWork(std::string Data){
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
    if (WorkMeth == "colors"){
        int startToX = DataToInt(Data, "StartX"), startToY = DataToInt(Data, "StartY"),
         endToX = DataToInt(Data, "endX"), endToY = DataToInt(Data, "endY");
        int rcsize = DataToInt(Data, "DataSize"), realsize;
        auto Colors = new char[rcsize];
        strcpy(Colors,DataToString(Data, "Colors").c_str());
        for(int i = 0; i < rcsize; i++){
            ScreenList[Sid]->Components_List[Cid]->Canvas_Components();
            realsize++;
        }
    }
    else if (WorkMeth == "resize"){
        
    }
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
            std::string BufData(recvBuffer);
            BufData.erase(0,15);
            Sea_Method_div(N_ID, In_Method, BufData);
        }
    }
}