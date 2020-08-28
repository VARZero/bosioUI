// Screen 하나의 생성, 처리, 출력, 소멸에 관한 코드

#include "Sea.h"
#include <random>

map <int, ScreenInfo*> ScreenList; 

void ScreenInfo::Create_Screen(){ // 랜덤으로 ID를 만들고, 스크린 정보를 ScreenList에 추가
    random_device dvSeed;
    mt19937 gen(dvSeed());
    uniform_int_distribution<int> dis(1000000,9999999);
    printf("aa\n");
    int tempid = dis(gen);
    if (ScreenList.find(tempid) == ScreenList.end()){
        Screen_ID = tempid;
        ScreenList.insert({Screen_ID,this});
    }
    else{Create_Screen();}
}

int ScreenInfo::Output_ScreenID(){
    return Screen_ID;
}

void ScreenInfo::Set_Screen(){
    // 스크린 영역을 생성합니다.
    Scr_x = Scr_x + 2*cos(M_PI*(angleUD/3))*sin(M_PI*(angleLR/3)); Scr_y = Scr_y + 2*sin(M_PI*(angleUD/3)); Scr_z = Scr_z - 2*cos(M_PI*(angleUD/3))*cos(M_PI*(angleLR/3)); //위치에 대응하는 좌표
    CE1line = sqrt(pow(sin(M_PI*(angleUD/3))*height,2)+pow(width,2));
    CE1sin = (sin(M_PI*(angleUD/3))*height)/CE1line;
    CE1cos = 0.7/CE1line;
    ED1sin = CE1line*(CE1sin*cos(M_PI*(angleLR/3))+CE1cos*sin(M_PI*(angleLR/3)));
    ED1cos = CE1line*(CE1cos*cos(M_PI*(angleLR/3))-CE1sin*sin(M_PI*(angleLR/3)));
    ED2sin = CE1line*(sin(M_PI*(angleLR/3))*CE1cos-cos(M_PI*(angleLR/3))*CE1sin);
    ED2cos = CE1line*(cos(M_PI*(angleLR/3))*CE1cos+sin(M_PI*(angleLR/3))*CE1sin);
    SEEy = cos(M_PI*(angleUD/3))*height;
    // 좌표 위치
    TopLeftx = Scr_x-ED2cos; TopLefty = Scr_y+SEEy; TopLeftz = Scr_z-ED2sin; // 좌상단
    TopRightx = Scr_x+ED1cos; TopRighty = Scr_y+SEEy; TopRightz = Scr_z+ED1sin; // 우상단
    BottomLeftx = Scr_x-ED1cos; BottomLefty = Scr_y-SEEy; BottomLeftz = Scr_z-ED1sin; // 좌하단
    BottomRightx = Scr_x+ED2cos, BottomRighty = Scr_y-SEEy; BottomRightz = Scr_z-ED2sin; // 우하단
    // 픽셀 하나당 크기(픽셀로 정하는 거)
    Px = (TopLeftx - TopRightx)/width;
    Py = (TopLefty - BottomLefty)/height;
    Pz = (TopLeftz - TopRightz)/width;
    for (auto NowComponent = Components_List.begin(); NowComponent != Components_List.end(); NowComponent++){
        // 컴포넌트의 리스트로 해서 변경사항 입력
        NowComponent->second->Resize_Components();
    }
}

void ScreenInfo::Draw_Screen(){
    for (auto NowComponent = Components_List.begin(); NowComponent != Components_List.end(); NowComponent++){
        // 컴포넌트의 리스트로 해서 출력
        NowComponent->second->Draw_Components();
        /* 컴포넌트에 현재 위치, 각도정보 처리하는건 Set_Screen쪽에서 동작하기때문에 여기는 그냥 출력만 하는걸로함 */
    }
}

void ScreenInfo::Add_Components(int x,int y, int w, int h, int d, string name){
    // 컴포넌트의 아이디 생성(랜덤 ID) 및 컴포넌트 정보 생성 
    random_device dvSeed;
    mt19937 gen(dvSeed());
    uniform_int_distribution<int> dis(100000,999999);
    printf("Components Create\n");
    int tempid = dis(gen);
    if (Components_List.find(tempid) == Components_List.end()){
        Components_Info *newComponent = new Components_Info(tempid,x,y,w,h,d,name,this);
        Components_List.insert({tempid, newComponent});
    }
    else{Add_Components(x,y,w,h,d,name);}
}

void ScreenInfo::Delete_Components(int ID){
    Components_Info* Component = Components_List[ID];
    Component->~Components_Info();
}
