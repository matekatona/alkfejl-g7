#ifndef DIAGCLIENT_H
#define DIAGCLIENT_H

#include <QMainWindow>

namespace Ui {
class DiagClient;
}

class DiagClient : public QMainWindow
{
public:
    explicit DiagClient(QWidget *parent = 0);
    ~DiagClient();

private:
    Ui::DiagClient *ui;
};

#endif // DIAGCLIENT_H
