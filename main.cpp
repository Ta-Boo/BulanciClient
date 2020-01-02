


#include <iostream>
#include "Comunication/ComunicationManager/ComunicationManager.h"

int main(int argc, char* argv[]) {

    ComunicationManager manager;
    manager.connectSocket(argv[1],atoi(argv[2]));
    Message mess;
    manager.activateListening();
    manager.sendMessage(&mess);
    manager.sendMessage(&mess);
    mess.exit = true;
    manager.sendMessage(&mess);
    manager.waitForFinish();

    return 0;
}