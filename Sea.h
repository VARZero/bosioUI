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
#include <math.h>

using namespace std;

class ScreenInfo;
class Components_Info;

extern map <int, ScreenInfo*> ScreenList; // 스크린 ID, 클래스의 포인터가 맵 형태로 저장됨; 띄워야 할 스크린 창 리스트
extern float px, py, pz; // 현재 위치에 대한 정보 (대부분 상황에서 이동하진 않고, 특수 상황에서만 이동하는 것으로 함)
extern float vx, vy, vz; // 보는 곳의 시점 벡터 (위치 벡터값을 저장하기 위해 있음, SeeLR이나 SeeUD과 동시에 동작하는 것으로 함)
extern float SeeLR, SeeUD; // 보는 곳의 각도 정보 (시점 벡터값의 상위값으로 이것이 메인으로 사용됨)

/*void See_Display(){ // 보는 곳의 각도를 시점 벡터로 변환해주기 위한 함수
    SeeLR;
}*/

class ScreenInfo{ // 스크린 하나에 대한 정보
    private:
        float x, y, z; // 위치 부분 x, y, z
        float angleLR, angleUD, Depth; // 위치정보 좌우, 위아래, 깊이
        string Screen_Name; // 스크린 이름 (지정해줘야 함)
        int Screen_ID; // 스크린 아이디 (생성시 랜덤으로 지정됨)
        map <int, Components_Info*> Components_List; // 컴포넌트 리스트
    public:
        ScreenInfo(string name, float x, float y, float z, float LR, float UD, float Dep, int *ScrID){ // 스크린 정보 생성시
            Screen_Name = name; // 스크린 이름 지정
            angleLR = LR; // 스크린 좌우 위치 지정
            angleUD = UD; // 스크린 위아래 지정
            Depth = Dep; // 스크린 깊이 지정
            Create_Screen(); // 스크린 ID를 생성하는 단계로 이동
        }
        void Create_Screen(); // 스크린 ID를 생성하고 스크린 정보를 메인 스크린 리스트(ScreenList)에 등록하는 목적의 함수
        void Set_Screen(); // 출력을 위해 처리하기 위한 함수
        void Draw_Screen(); // 스크린을 표시하기 위해 사용하는 함수, OpenGL 스크린 출력 함수에서 사용됨
        void Add_Components(int, Components_Info*); // 컴포넌트를 추가하기 위한 함수
        void Delete_Components(int Components_ID); // 컴포넌트를 삭제하기 위한 함수
        ~ScreenInfo(){ // 스크린 삭제
            ScreenList.erase(Screen_ID); // 스크린 정보를 지움
        } 
};

class Components_Info{ // 컴포넌트 하나에 관련된 정보
    private:
        int X, Y, sizeX, sizeY; // 컴포넌트 위치에 대한 변수
        string name; // 컴포넌트 이름에 대한 변수
        int Components_ID; // 컴포넌트 식별 아이디
        ScreenInfo *parents; // 컴포넌트에 위치하는 스크린에 대한 정보
    public:
        Components_Info(int xx,int yy, int weight, int height, string Inputname,ScreenInfo* par){
            X = xx; Y== yy; sizeX = weight; sizeY = height; name = Inputname; *parents = *par;
            Create_Components();
        }
        void Create_Components(); // 컴포넌트 ID를 생성하고 부모스크린에 컴포넌트 정보를 추가함
        void Canvas_Components(); // 컴포넌트에 무언가를 그려 넣을때
        void Event_Components(string eventName); // 이벤트가 발생했을때
        void Draw_Components(); // 컴포넌트를 출력할때
        ~Components_Info(){ // 컴포넌트가 삭제될때
            parents -> Delete_Components(Components_ID); // 스크린에서 컴포넌트 정보를 삭제
        }
};
