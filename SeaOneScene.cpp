#include "Sea.h"
#include <time.h>

map <int, ScreenInfo*> ScreenList; 

void ScreenInfo::Create_Screen(){ // 랜덤으로 ID를 만들고, 스크린 정보를 ScreenList에 추가
    srand((unsigned int)time(NULL));
    int tempid = rand();
    if (ScreenList.find(tempid) != ScreenList.end()){
        Screen_ID = tempid;
        ScreenList.insert({Screen_ID,this});
    }
    else{Create_Screen();}
}

void ScreenInfo::Set_Screen(){
    //
    
}

void ScreenInfo::Draw_Screen(){
    
}

void ScreenInfo::Add_Components(int Compon_ID, Components_Info* Compon_Pointer){
    Components_List.insert({Compon_ID, Compon_Pointer});
}

void ScreenInfo::Delete_Components(int ID){
    Components_Info* Component = Components_List[ID];
    //Components_Info();
}