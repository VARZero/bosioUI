# bosioUI
BosioUI(보시오 유-아이)는 VR, AR, mr디바이스 시스템에서 근, 원거리 통신 GUI 시스템을 구성하기 위한 토이 프로젝트입니다.<br>
UDP 프로토콜을 사용하는 커스텀 프로토콜인 **Sea**와 그것을 출력하기 위해 **보시오(Bosio)** 로 구성되고 있습니다.<br>
최종적으로 LAPUTA팀에 기여하기 위해 개발을 진행하고 있습니다.<br>
<br><br>
Sea 프로토콜에 대한 자세한 정보는 Sea저장소와 저장소의 위키를 참조해 주십시오.<br>
## 보시오(Bosio)란?
**보시오) Bosio, 이하 강조된 "보시오"로 표기합니다**는 Sea 프로토콜이 어떻게 처리되고, HMD디바이스에서 어떻게 보여줄 수 있는지 나타내 주는 프로젝트 입니다.<br>
### "보시오"의 구성
**보시오**는 여러 부분이 연결되어 있습니다.
- **화면을 출력하기 위한 부분** | OpenGL API를 사용합니다. 말 그대로 화면을 출력하기 위한 부분입니다. (SeaDraw.cpp)
- **Sea프로토콜을 처리하는 부분** | 화면에 출력하기 위해 Sea프로토콜에서 스크린과 컴포넌트 생성, 이벤트 처리등을 처리합니다. (SeaNetworkTABLE.cpp)
- **보시오에서 사용하는 스크린, 컴포넌트 처리하는 부분** | **보시오**에서는 화면을 출력하는데 큰 부분에서 Screen이라는 개념을, 작은부분에서는 Component라는 개념을 사용합니다. (SeaOneScene.cpp, SeaComponents.cpp)
- **이 모든것을 실행하는 부분** | 스레드 분배를 하기 위해 사용되는 부분입니다. (bosio.cpp)
변수, 클래스 선언 한 헤더파일도 있습니다. (Sea.h)<br>
<br>
Sea.h에  자세한 내용은 이 저장소의 위키를 참조해 주세요.<br>

## 사용한 라이브러리
1. TinyXML2 <br>[Commit version: 1aeb57d26bc303d5cfa1a9ff2a331df7ba278656]<br>(zlib license) <br>https://github.com/leethomason/tinyxml2.git
2. FreeGLUT

## 라이선스
이 프로젝트는 MIT License를 사용합니다.

MIT License

Copyright (c) 2020 신성민

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## 현재상황
현재는 아직 시스템 전체가 구성되지 않았습니다. 그래서 당장 제대로된 구동이 될 일이 없습니다.(..)<br>
되는대로 이 문서를 갱신하겠습니다. 아마, makefile을 실행시키고, sh를 실행하면 구동되게 만들어 질 것 같습니다.<br>

## 여담
미숙한 프로그래밍 실력에 부끄럽습니다.. 언젠가 실력이 좀 늘면 Sea프로토콜을 쓰는 제대로 된 C++ 문법으로 작성된 프로젝트를 만들겠습니다..ㅠㅠ 