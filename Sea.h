#ifdef __APPLE__
    //맥에서 테스트를 위해 추가
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <GLUT/glut.h>
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
    #endif
#elif __linux__
    //메인 시스템은 리눅스 기반으로 구동
    #include <GL/gl.h>
    #include <GL/glut.h>
    #include <GL/glu.h>
    #endif 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

using namespace std;

extern map <int, ScreenInfo*> ScreenList; // 스크린 ID, 클래스의 포인터가 맵 형태로 저장됨; 띄워야 할 스크린 창 리스트

class ScreenInfo{ // 스크린 하나에 대한 정보
    private:
        float angleLR, angleUD, Depth; // 위치정보
        string Screen_Name;
        int Screen_ID;
        map <int, int> Components_List;
    public:
        ScreenInfo(string name, float LR, float UD, float Dep, int *ScrID){
            Screen_ID = 1231;
            Screen_Name = name;
            angleLR = LR;
            angleUD = UD;
            Depth = Dep;
            Create_Screen();
        }
        void Create_Screen();
        void Remove_Screen();
        void Draw_Screen();
        void Add_Componets();
        void Delete_Componets(int Components_ID);
        ~ScreenInfo(){
            ScreenList.erase(Screen_ID);
        }
};

class Components_Info{ // 컴포넌트 하나에 관련된 정보
    private:
        int X, Y, fixX, fixY;
        string name;
        int Components_ID;
        ScreenInfo *parents;
    public:
        Components_Info(int X,int Y,int fixX,int fixY,string name,ScreenInfo* par);
        void ComponentsEvent(string eventName);
        ~Components_Info(){
            parents -> Delete_Componets(Components_ID);
        }
};

//void create_Screen(string name, float LR, float UD, float Dep);
