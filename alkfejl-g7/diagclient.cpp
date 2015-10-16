#include "diagclient.h"
#include "ui_diagclient.h"

DiagClient::DiagClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiagClient)
{
    ui->setupUi(this);
}

DiagClient::~DiagClient()
{
    delete ui;
}
