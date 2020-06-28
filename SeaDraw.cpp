#include "Sea.h"

static float angleLR = 0.0, angleUD = 0.0, ratio; //시점 각도
static float px = 0.0f, py = 1.75f, pz = 5.0f; //현재 위치
static float lx = 0.0f, ly = 0.0f, lz = -1.0f; //보는 곳 위치벡터
static float mx, my, pastX,pastY; //마우스 움직여서 화면 시점이동 관련

void renderScreen(){
    //바닥 - 삭제예정
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0,0.0,-100.0);
        glVertex3f(-100.0,0.0,100.0);
        glVertex3f(100.0,0.0,100.0);
        glVertex3f(100.0,0.0,-100.0);
    glEnd();
    
    glFlush();
}

int main(int argc, char **argv){
    //-메- 인
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(960,540);
    glutCreateWindow("LAPUTA-UI");

    glutKeyboardFunc(keyboardKeyCheck);
    glutSpecialFunc(debug_inputkey);
    glutPassiveMotionFunc(mouseMoveAndScreen);

    glutDisplayFunc(renderScreen);
    glutIdleFunc(renderScreen);

    glutReshapeFunc(See_Screen);
    glutMainLoop();
}