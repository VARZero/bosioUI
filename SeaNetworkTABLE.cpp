// Sea 프로토콜의 처리를 위해 사용되는 코드

#include "Sea.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>

//map <int, map<std::string, std::string>> SeaNetworkID; // 데이터 재검증을 위해 저장하는 map

int Sock_Server; // 전송용 소켓
short i; // 임시변수
std::mutex Mut;

// 데이터에서 해당 타입의 변수로 변환시켜 주는 함수
std::string DataToString(std::string inData,std::string MethodName){
    size_t tempstart, tempend;
    tempstart = inData.find(MethodName+':');
    if (tempstart == -1){
        return "";
    }
    tempend = inData.find('\t',tempstart + MethodName.size() + 2);
    return inData.substr(tempstart + MethodName.size() + 2, tempend - tempstart - MethodName.size() - 2);
}
int DataToInt(std::string inData,std::string MethodName){
    std::string temptxt;
    size_t tempstart, tempend;
    tempstart = inData.find(MethodName+':');
    if (tempstart == -1){
        return 0;
    }
    tempend = inData.find('\t',tempstart + MethodName.size() + 2);
    temptxt = inData.substr(tempstart + MethodName.size() + 2, tempend - tempstart - MethodName.size() - 2);
    return stoi(temptxt);
}
float DataToFloat(std::string inData,std::string MethodName){
    std::string temptxt;
    size_t tempstart, tempend;
    tempstart = inData.find(MethodName+':');
    if (tempstart == -1){
        return 0;
    }
    tempend = inData.find('\t',tempstart + MethodName.size() + 2);
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
    cout << SName << endl;
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

    todo// 추가적으로 기본 템플릿 받아오게 하기

    cout << SName << Sx << Sh << ScrLR << endl;
    ScreenInfo *OneScn = new ScreenInfo(SName, Sx, Sy, Sz, Sh, Sw, ScrLR, ScrUD);
    // 생성된 스크린 아이디 전송
    Mut.lock();
    Sid = OneScn->Output_ScreenID();
    Mut.unlock();
    cout << Sid << " Sid" << endl;
    char sendBuf[34], SidC[9]; // = { *network_ID + (char *) "SREVERSEScreenID:" + Sid };
    sprintf(SidC, "%d", Sid);
    strcpy(sendBuf, network_ID);
    strcat(sendBuf, "SCRREVESID: ");
    strcat(sendBuf, SidC);
    cout << sendBuf << endl;

    ssize_t SendScrID = sendto(Sock_Server, sendBuf, strlen(sendBuf), 0, (struct sockaddr*)&cliAddr, sizeof(cliAddr));
    cout << SendScrID << endl;
    if(SendScrID != strlen(sendBuf)){
        cout << strlen(sendBuf) << endl;
        printf("error! I can't send Screen ID!\n");
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
    char sendBuf[34], CidC[9]; // = { *network_ID + (char *) "SREVERSEScreenID:" + Sid };
    sprintf(CidC, "%d", Cid);
    strcpy(sendBuf, network_ID);
    strcat(sendBuf, "CPTREVESID: ");
    strcat(sendBuf, CidC);

    ssize_t SendScrID = sendto(Sock_Server, sendBuf, strlen(sendBuf), 0, (struct sockaddr*)&cliAddr, sizeof(cliAddr));
    if(SendScrID != strlen(sendBuf)){
        cout << strlen(sendBuf) << endl;
        printf("error! I can't send Components ID!\n");
    }
}

void ComponentsEventWork(std::string Data, char* network_ID, struct sockaddr_in cliAddr){
    // 이벤트 전달
    /*int Sid, Cid; // 스크린 아이디, 컴포넌트 아이디
    std::string Event;
    Sid = DataToInt(Data, "ScreenID");
    Event = DataToString(Data, "Event");
    if (Event == "Click"){
        // 클릭시
        float CliLR, CliUD;
        CliLR = DataToFloat(Data, "LR");
        CliUD = DataToFloat(Data, "UD");
    }
    else if (Event == "KeyPress"){
        // 키보드 키 입력
        char Key = (char) DataToString(Data, "Key").c_str();
    }
    else if (Event == "Scroll"){
        // 스크롤
    }
    else if (Event == "FnEvent"){
        // 제스쳐 같은 특수 이벤트

    }*/
}

void ScreenMotifyWork(std::string Data){
    // 스크린 이름, 사이즈 수정
    int Sid = DataToInt(Data, "ScreenID");
    std::string WorkMeth = DataToString(Data, "ScMotify");
    ScreenInfo* editSc = ScreenList[Sid];
    if (WorkMeth == "Name"){
        std::string name = DataToString(Data, "NewName");
        editSc->NameEdit_Screen(name);
    }
    else if (WorkMeth == "Size"){
        float mx = DataToFloat(Data, "X");
        float my = DataToFloat(Data, "Y");
        float mz = DataToFloat(Data, "Z");
        float mLR = DataToFloat(Data, "LR");
        float mUD = DataToFloat(Data, "UD");

        editSc->SizeEdit_Screen(mx, my, mz, mLR, mUD);
    }
}

void ComponentsMotifyWork(std::string Data){
    // 컴포넌트 내용물, 사이즈 수정
    int Sid = DataToInt(Data, "ScreenID"), Cid = DataToInt(Data, "ComponentsID");
    std::string WorkMeth = DataToString(Data, "CmMotify");
    if (WorkMeth == "Size"){
        // 사이즈 변경
        int mx = DataToInt(Data, "x");
        int my = DataToInt(Data, "y");
        int mw = DataToInt(Data, "w");
        int mh = DataToInt(Data, "h");
        int md = DataToInt(Data, "d");
        Mut.lock();
        ScreenList[Sid]->Components_List[Cid]->Resize_Components(mx, my, mw, mh, md);
        Mut.unlock();
    }
    else if (WorkMeth == "Points"){
        // 내용물 (캔버스)변경 (이미지, 커스텀 버튼 전용)
        int width = DataToInt(Data, "width");
        int height = DataToInt(Data, "height");
        int length = DataToInt(Data, "Length");
        std::string ColorDatas = DataToString(Data, "Colors");
        char* getColors = new char[length*4];
        getColors = (char*) ColorDatas.c_str();
        Mut.lock();
        ScreenList[Sid]->Components_List[Cid]->Canvas_Components(width, height, length, getColors);
        Mut.unlock();
    }
}

int Sea_Method_div(char *Network_ID, const char *Method, std::string Data, struct sockaddr_in cliAddr){
    // Sea 프로토콜의 메소드에 따른 정의
    //((const char *) Method == "SCCREATE")
    if (strcmp(Method, "SCCREATE") == 0){
        // 스크린 생성
        std::thread* work = new std::thread(ScreenCreateWork, Data, std::ref(Network_ID), cliAddr);
        work->join();
        delete work;
    }
    else if (strcmp(Method,"CMCREATE") == 0){
        // 컴포넌트 생성
        std::thread* work = new std::thread(ComponentsCreateWork, Data, std::ref(Network_ID), cliAddr);
        work->join();
        delete work;
    }
    else if (strcmp(Method, "EVENT"+0x00+0x00+0x00) == 0){
        // 이벤트
        std::thread* work = new std::thread(ComponentsEventWork, Data, std::ref(Network_ID), cliAddr);
        work->join();
        delete work;
    }
    else if (strcmp(Method, "SCMODIFY") == 0){
        // 스크린 수정
        std::thread* work = new std::thread(ScreenMotifyWork, Data);
        work->join();
        delete work;
    }
    else if (strcmp(Method, "CMMODIFY") == 0){
        // 컴포넌트 수정
        std::thread* work = new std::thread(ComponentsMotifyWork, Data);
        work->join();
        delete work;
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
    Sock_Server = socket(AF_INET, SOCK_DGRAM, 0);
    if(Sock_Server == -1){
        printf("Socket Error");
        return;
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(22117);
    printf("%x %x\n", serverAddr.sin_addr.s_addr, serverAddr.sin_port);
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
            char N_ID[9], In_Method[9];
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
            std::string BufData(recvBuffer);
            BufData.erase(0,15);
            printf("%x %x %ld\n", clientAddr.sin_addr.s_addr, clientAddr.sin_port, sizeof(clientAddr));
            if (Sea_Method_div(N_ID, In_Method, BufData, clientAddr) == 1){
                continue;
            }
        }
    }
}