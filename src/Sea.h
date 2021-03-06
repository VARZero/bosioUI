#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <map>
#include <mutex>
#include <string>
#include <list>

using namespace std;

class ScreenInfo;
class Components_Info;

extern std::mutex Mut; // 뮤텍스

extern map <int, ScreenInfo*> ScreenList; // 스크린 ID, 클래스의 포인터가 맵 형태로 저장됨; 띄워야 할 스크린 창 리스트
extern float px, py, pz; // 현재 위치에 대한 정보 (대부분 상황에서 이동하진 않고, 특수 상황에서만 이동하는 것으로 함)
extern float vx, vy, vz; // 보는 곳의 시점 벡터 (위치 벡터값을 저장하기 위해 있음, SeeLR이나 SeeUD과 동시에 동작하는 것으로 함)
extern float SeeLR, SeeUD; // 보는 곳의 각도 정보 (시점 벡터값의 상위값으로 이것이 메인으로 사용됨)

/*void See_Display(){ // 보는 곳의 각도를 시점 벡터로 변환해주기 위한 함수
    SeeLR;
}*/

class ScreenInfo{ // 스크린 하나에 대한 정보
    private:
        // 지정하는것들
        float Scr_x, Scr_y, Scr_z; // 위치 부분 x, y, z
        float angleLR, angleUD; // 위치정보 좌우, 위아래
        string Screen_Name; // 스크린 이름 (지정해줘야 함)
        bool SeeFix; //시점고정
        // 내부에서 알아서 설정되는것들
        int Screen_ID; // 스크린 아이디 (생성시 랜덤으로 지정됨)
            // 아래는 Set_Screen함수를 통해 설정됨
        float CE1line, CE1sin, CE1cos, ED1sin, ED1cos, ED2sin, ED2cos, SEEy;
    public:
        std::string ScrTemplate;
        map <int, Components_Info*> Components_List; // 컴포넌트 리스트
        float TopLeftx, TopLefty, TopLeftz, TopRightx, TopRighty, TopRightz, 
        BottomLeftx, BottomLefty, BottomLeftz, BottomRightx, BottomRighty, BottomRightz; // 좌표상 위치
        float Px, Py, Pz; // 픽셀 하나당 크기
        float height, width; // 높, 너비
        std::thread ScreenThread; // 이벤트 처리를 위한 쓰레드
        ScreenInfo(string name, float x, float y, float z, float h, float w, float LR, float UD){ // 스크린 정보 생성시
            Scr_x = x; Scr_y = y; Scr_z = z;
            height = h; width = w;
            Screen_Name = name; // 스크린 이름 지정
            angleLR = LR; // 스크린 좌우 위치 지정
            angleUD = UD; // 스크린 위아래 지정
            Create_Screen(); // 스크린 ID를 생성하는 단계로 이동
        }
        void Create_Screen(); // 스크린 ID를 생성하고 스크린 정보를 메인 스크린 리스트(ScreenList)에 등록하는 목적의 함수
        void NameEdit_Screen(std::string); // 스크린 이름을 수정함
        void SizeEdit_Screen(float, float, float, float, float); // 스크린의 위치를 이동하기 위해 사용
        int Output_ScreenID(); // 스크린 ID를 외부로 출력하기 위해 사용
        void Set_Screen(); // 출력을 위해 처리하기 위한 함수
        void Draw_Screen(); // 스크린을 표시하기 위해 사용하는 함수, OpenGL 스크린 출력 함수에서 사용됨
        void Add_Components(int, int, int, int, int, string, int*); // 컴포넌트를 추가하기 위한 함수
        void Delete_Components(int Components_ID); // 컴포넌트를 삭제하기 위한 함수
        ~ScreenInfo(){ // 스크린 삭제
            ScreenList.erase(Screen_ID); // 스크린 정보를 지움
        }
};

class Components_Info{ // 컴포넌트 하나에 관련된 정보
    private:
        int X, Y, sizeX, sizeY, Depth; // 컴포넌트 위치에 대한 변수
        string name; // 컴포넌트 이름에 대한 변수
        int Components_ID; // 컴포넌트 식별 아이디
        ScreenInfo *parents; // 컴포넌트에 위치하는 스크린에 대한 정보
        int *colorList; // 색상, 투명도 정보
    public:
        float LTx, LTy, LTz, LBx, LBy, LBz, RTx, RTy, RTz, RBx, RBy, RBz; // 좌표 위치
        Components_Info(int Cid, int xx,int yy, int weight, int height, int indepth, string Inputname, ScreenInfo* par){
            Components_ID = Cid; X = xx; Y = yy; sizeX = weight; sizeY = height; Depth = indepth; name = Inputname; parents = par;
            colorList = new int[(sizeX*sizeY)];
        }
        void Resize_Components(int, int, int, int, int); // 컴포넌트의 크기를 변경할때 사용
        void Canvas_Components(int, int, int, char*); // 컴포넌트에 무언가를 그려 넣을때
        void Event_Components(string eventName, string eventdata); // 이벤트가 발생했을때
        void Draw_Components(); // 컴포넌트를 출력할때
        ~Components_Info(){ // 컴포넌트가 삭제될때
            parents -> Delete_Components(Components_ID); // 스크린에서 컴포넌트 정보를 삭제
        }
};

class Components_Model3D{ // 3D 모델에 대한 정보
    private:
        int Mod_x, Mod_y, Mod_z, Mod_LR, Mod_UD, Mod_La; // 위치및 방향에 대한 정보
        // 모델의 x, y, z좌표, 기울어진 방향 (좌우, 상하, 정면에서 봤을때 회전)
        string name;
        int Model_ID; // 모델 식별 아이디
        
};

extern void Screen_Main(int, char);
extern void Net_Sea_Table();

//extern map <int, map<std::string, std::string>> SeaNetworkID; // 데이터 재검증을 위해 저장하는 map