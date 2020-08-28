// 컴포넌트 처리를 위해 사용되는 코드

#include "Sea.h"

void Components_Info::Resize_Components(){
    //컴포넌트 사이즈 변경 (위치 변경시에서도 동작합니다!)
    LTx = (parents->Px)*X; LTy = (parents->Py)*Y; LTz = (parents->Pz)*X;
    RTx = (parents->Px)*(X+sizeX); RTy = (parents->Py)*Y; RTz = (parents->Pz)*(X+sizeX);
    LBx = (parents->Px)*X; LBy = (parents->Py)*(Y+sizeY); LBz = (parents->Pz)*X;
    RBx = (parents->Px)*(X+sizeX); RBy = (parents->Py)*(Y+sizeY); RBz = (parents->Pz)*(X+sizeX);
}
void Components_Info::Canvas_Components(){
    // 컴포넌트 모양 그려넣기

}

void Components_Info::Event_Components(string eventname){
    // 이벤트 발생시 실행되는 코드
}

void Components_Info::Draw_Components(){
    // 출력을 위해 존재함 (단순히 출력만 함)
    
}