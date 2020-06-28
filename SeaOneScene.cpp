#include "Sea.h"

map <int, ScreenInfo*> ScreenList; 

/*void create_Screen(string name, float LR, float UD, float Dep){
    int *ScreenID;
     = new ScreenInfo(name, LR, UD, Dep, ScreenID);
    ScreenList.insert({,});
}*/

void ScreenInfo::Create_Screen(){
    int tempid = 132;
    if (ScreenList.find(tempid) != ScreenList.end()){
        ScreenList.insert({Screen_ID,this});
    }
}