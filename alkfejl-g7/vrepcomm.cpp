#include "vrepcomm.h"

VREPComm::VREPComm(QObject *parent) : QObject(parent)
{

}

void VREPComm::connect(int port)
{
    socket.connectToHost("127.0.0.1", this->port=port);
}
