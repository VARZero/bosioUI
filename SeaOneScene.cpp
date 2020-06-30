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
    else{Create_Screen()}
}