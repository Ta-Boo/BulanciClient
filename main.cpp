


#include <iostream>
#include "Comunication/ComunicationManager/ComunicationManager.h"

int main(int argc, char* argv[]) {

    ComunicationManager manager;
    manager.connectSocket(argv[1],atoi(argv[2]));
    Message mess;
    cout << " here"<<endl;
    sleep(1);
    sleep(1);
    for (int i = 0; i < 10; ++i) {
        manager.sendMessage(&mess);
        sleep(1);
    }
    sleep(10);
    return 0;
}