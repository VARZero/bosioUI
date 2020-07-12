// 컴포넌트 처리를 위해 사용되는 코드

#include "Sea.h"

void Components_Info::Create_Components(){ // 컴포넌트 아이디를 랜덤으로 생성 시킴
    srand((unsigned int)time(NULL));
    int tempid = rand();
    if (ScreenList.find(tempid) != ScreenList.end()){
        Components_ID = tempid;
        parents -> Add_Components(Components_ID, this);
    }
    else{Create_Components();}
}

void Components_Info::Canvas_Components(){
    // 컴포넌트 모양 그려넣기
}

void Event_Components(string eventname){
    // 이벤트 발생시 실행되는 코드
}

void Draw_Components(){
    // 출력을 위해 존재함 (단순히 출력만 함)
}