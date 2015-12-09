#ifndef LINESENSOR_H
#define LINESENSOR_H


#include "simcomm.h"

#define LINE_THRESHOLD 0.5f

class LineSensor : public SimComm
{
    Q_OBJECT
public:
    LineSensor();
    QVarLengthArray<bool> getValues();

private slots:
    void reset_cache();

private:
    std::shared_ptr<QVarLengthArray<bool>> pvalues;

    std::weak_ptr<QVarLengthArray<bool>> cachevalues;
};

#endif // LINESENSOR_H
