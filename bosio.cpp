#include <thread>
#include "Sea.h"

int main(int argc, char **argv){
    std::thread Screen_Thread(Screen_Main, argc, **argv);
    std::thread SeaNet_Thread(Net_Sea_Table);

    Screen_Thread.join();
    SeaNet_Thread.join();

    return 0;
}