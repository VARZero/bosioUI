// 컴포넌트 처리를 위해 사용되는 코드

#include "Sea.h"

void Components_Info::Move_Components(){
    // 컴포넌트 위치 이동
}

void Components_Info::Resize_Components(){
    //컴포넌트 사이즈 변경 (위치 변경시에서도 동작합니다!)
    /* 
    임시 메모
        여기에 부모 스크린의 꼭지점 정보를 가져와서 처리하게끔 작성할거임
    */
    LTx = parents->TopLeftx - parents->BottomLeftx;
}

void Components_Info::Canvas_Components(){
    // 컴포넌트 모양 그려넣기

}

void Components_Info::Shape_Components(){
    // 컴포넌트의 보이는 모양을 적용시키기 위해 사용
}

void Components_Info::Event_Components(string eventname){
    // 이벤트 발생시 실행되는 코드
}

void Components_Info::Draw_Components(){
    // 출력을 위해 존재함 (단순히 출력만 함)
    
}