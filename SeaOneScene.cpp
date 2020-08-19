// Screen 하나의 생성, 처리, 출력, 소멸에 관한 코드

#include "Sea.h"
#include <random>

map <int, ScreenInfo*> ScreenList; 

int ScreenInfo::Create_Screen(){ // 랜덤으로 ID를 만들고, 스크린 정보를 ScreenList에 추가
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

void ScreenInfo::Set_Screen(){
    // 스크린 영역을 생성합니다.
    
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
