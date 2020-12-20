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