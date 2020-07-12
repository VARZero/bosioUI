// https://sungcheol-kim.gitbook.io/glut-tutorials 를 어느정도 참조 했습니다. 김성철님 좋은 튜토리얼 감사합니당
// OpenGL에서 화면 출력을 위해 사용되는 부분

#include "Sea.h"

float ratio;

// 아래 3줄은 Sea.h참조
float px = 0.0f, py = 1.65f, pz = 0.0f;
float vx = 0.0f, vy = 0.0f, vz = -1.0f;
float SeeLR = 0.0, SeeUD = 0.0;

void changeSize(int w, int h)
{
    if(h == 0)
        h = 1;

    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(px, py, pz, px + vx , py + vy , pz + vz , 0.0f,1.0f,0.0f);
}

void floorInScreen(){
    glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
}

void renderDISP(){
    // 디버깅용으로 땅 넣을예정
    floorInScreen();
    // 모든 스크린 출력
    for (auto OneScreen = ScreenList.begin();OneScreen != ScreenList.end();OneScreen++){
        // 스크린의 리스트로 해서 출력
        OneScreen->second->Draw_Screen();
    }
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640,480);
    glutCreateWindow("BOSIO");

    glutDisplayFunc(renderDISP);
    glutIdleFunc(renderDISP);

    glutReshapeFunc(changeSize);

    glutMainLoop();

    return 0;
}