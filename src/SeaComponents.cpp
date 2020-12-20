// 컴포넌트 처리를 위해 사용되는 코드

#include "Sea.h"

void Components_Info::Resize_Components(int mx, int my, int mw, int mh, int md){
    //컴포넌트 사이즈 변경 (위치 변경시에서도 동작해야 합니다!)
    if (mx != NULL) {X = mx;}
    if (my != NULL) {Y = my;}
    if (mw != NULL) {sizeX = mw;}
    if (mh != NULL) {sizeY = mh;}

    LTx = (parents->Px)*(X/10); LTy = (parents->Py)*(Y/10); LTz = (parents->Pz)*(X/10);
    RTx = (parents->Px)*((X+sizeX)/10); RTy = (parents->Py)*(Y/10); RTz = (parents->Pz)*((X+sizeX)/10);
    LBx = (parents->Px)*(X/10); LBy = (parents->Py)*((Y+sizeY)/10); LBz = (parents->Pz)*(X/10);
    RBx = (parents->Px)*((X+sizeX)/10); RBy = (parents->Py)*((Y+sizeY)/10); RBz = (parents->Pz)*((X+sizeX)/10);
}
void Components_Info::Canvas_Components(int startX, int startY, int length, char* Colors){
    // 컴포넌트 모양 그려넣기(이미지 기준)
    for(int i = 0; i < length; ++i){
        
    }
}

void Components_Info::Event_Components(string eventname, string eventdata){
    // 이벤트 발생시 실행되는 코드
}

void Components_Info::Draw_Components(){
    // 출력을 위해 존재함 (단순히 출력만 함)
    
}