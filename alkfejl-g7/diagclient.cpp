#include "diagclient.h"
#include "ui_diagclient.h"

DiagClient::DiagClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiagClient)
{
    ui->setupUi(this);
    SetupConnections();
}

void DiagClient::AnyNewDataAvailable()
{
    if(robot.isReadyRead()) ui->textLogCtl->append(robot.recvAll());
    if(robot.getAccel()->isReadyRead())     ui->textLogAccel->append(robot.getAccel()->recvAll());
    if(robot.getGyro()->isReadyRead())      ui->textLogGyro->append(robot.getGyro()->recvAll());
    if(robot.getLineSens()->isReadyRead())  ui->textLogLine->append(robot.getLineSens()->recvAll());
}

void DiagClient::SetupConnections()
{
    try
    {
        robot.init();
        QObject::connect(&robot,                SIGNAL(readyRead()), this, SLOT(AnyNewDataAvailable()));
        QObject::connect(robot.getAccel(),      SIGNAL(readyRead()), this, SLOT(AnyNewDataAvailable()));
        QObject::connect(robot.getGyro(),       SIGNAL(readyRead()), this, SLOT(AnyNewDataAvailable()));
        QObject::connect(robot.getLineSens(),   SIGNAL(readyRead()), this, SLOT(AnyNewDataAvailable()));
    }
    catch(std::exception & e)
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Error in SetupConnections(): ") +QString(e.what()));
        msgBox.exec();
    }
}

DiagClient::~DiagClient()
{
    delete ui;
}

void DiagClient::sendFromLineEdit(QLineEdit* theLineEdit, QTextEdit* theLogControl, VREPComm* commObject)
{
    QString toSend = theLineEdit->text()+"\n";
    theLogControl->append(toSend);
    commObject->send(toSend);
    theLineEdit->clear();
}

void DiagClient::on_lineSendCtl_returnPressed()     { sendFromLineEdit(ui->lineSendCtl, ui->textLogCtl, &robot); }
void DiagClient::on_lineSendLine_returnPressed()    { sendFromLineEdit(ui->lineSendLine, ui->textLogLine, robot.getLineSens()); }
void DiagClient::on_lineSendAccel_returnPressed()   { sendFromLineEdit(ui->lineSendAccel, ui->textLogAccel, robot.getAccel()); }
void DiagClient::on_lineSendGyro_returnPressed()    { sendFromLineEdit(ui->lineSendGyro, ui->textLogGyro, robot.getGyro()); }
void DiagClient::on_btnSendCtl_clicked()            { on_lineSendCtl_returnPressed(); }
void DiagClient::on_btnSendLine_clicked()           { on_lineSendLine_returnPressed(); }
void DiagClient::on_btnSendAccel_clicked()          { on_lineSendAccel_returnPressed(); }
void DiagClient::on_btnSendGyro_clicked()           { on_lineSendGyro_returnPressed(); }
