#include "vrepcomm.h"

VREPComm::VREPComm(QObject *parent) : QObject(parent)
{
    QObject::connect(&socket,SIGNAL(readyRead()),this,SIGNAL(readyRead()));
}

bool VREPComm::isReadyRead() {  return socket.isReadable(); }

void VREPComm::connect(int port)
{
    socket.connectToHost("127.0.0.1", this->port=port);
    if(!socket.waitForConnected(100)) //should replace this with signals
    { throw std::runtime_error("Could not connect to socket!"); }

}

void VREPComm::send(QString data)
{
    socket.write(data.toStdString().c_str(),data.length());
}

//untested
//reads one line (ending with '\n' from the socket)
QString VREPComm::recvUntilNewline()
{
    if(!allDataReceived.contains("\n")) allDataReceived+=socket.readAll();
    if(allDataReceived.contains("\n"))
    {
        int chopUntil = allDataReceived.indexOf("\n");
        QString toReturn = allDataReceived.left(chopUntil);
        allDataReceived=allDataReceived.mid(chopUntil);
        return allDataReceived;
    }
    else return "";
}

QString VREPComm::recvAll()
{
    QString toReturn = allDataReceived + socket.readAll();
    allDataReceived = "";
    return toReturn;
}
