#ifndef DIAGCLIENT_H
#define DIAGCLIENT_H

#include <QMainWindow>
#include "robot.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QTextEdit>

namespace Ui {
class DiagClient;
}

class DiagClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit DiagClient(QWidget *parent = 0);
    ~DiagClient();
    void SetupConnections();

private slots:
    void AnyNewDataAvailable();

    void on_lineSendCtl_returnPressed();
    void on_lineSendLine_returnPressed();
    void on_lineSendAccel_returnPressed();
    void on_lineSendGyro_returnPressed();
    void on_btnSendCtl_clicked();
    void on_btnSendLine_clicked();
    void on_btnSendAccel_clicked();
    void on_btnSendGyro_clicked();

private:
    Ui::DiagClient *ui;
    Robot robot;
    void sendFromLineEdit(QLineEdit* theLineEdit, QTextEdit* theLogControl, VREPComm* commObject);
};

#endif // DIAGCLIENT_H
