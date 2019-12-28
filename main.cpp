#include "Comunication/Socket/Socket.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{

Socket socket1 = Socket();
    if(socket1.connectSocket(argv[1],atoi(argv[2])) != 0) {
        return  1;
    }
socket1.activateSocket();
    return 0;
}