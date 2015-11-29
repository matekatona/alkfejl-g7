#include "robothistory.h"

RobotHistory::RobotHistory(int length)
{
    this->maxLength = length;
}

QVarLengthArray<bool> RobotHistory::getLastLine(){
    return this->historyLine.last();
}
QVarLengthArray<float> RobotHistory::getLastAccel(){
    if(historyAccel.length()==0)
        return QVarLengthArray<float>({NAN, NAN, NAN});
    else
        return this->historyAccel.last();
}

QVarLengthArray<float> RobotHistory::getLastGyro(){
    if(historyGyro.length()==0)
        return QVarLengthArray<float>({NAN, NAN, NAN});
    else
        return this->historyGyro.last();
}

QVarLengthArray<float> RobotHistory::getLastWheels(){
    if(historyWheel.length()==0)
        return QVarLengthArray<float>({NAN, NAN});
    else
        return this->historyWheel.last();
}

void RobotHistory::addNewLineData(QVarLengthArray<bool> data){
    this->insertNewLineData(data);

    if(this->state[0]){
        if(this->state[1])
            this->state[1]=false;
        else
            this->insertNewAccelData();

        if(this->state[2])
            this->state[2]=false;
        else
            this->insertNewGyroData();

        if(this->state[3])
            this->state[3]=false;
        else
            this->insertNewWheelData();
    }
    else
        this->state[0]=true;
}

void RobotHistory::addNewAccelData(QVarLengthArray<float> data){
    this->insertNewAccelData(data);

    if(this->state[1]){
        if(this->state[0])
            this->state[0]=false;
        else
            this->insertNewLineData();

        if(this->state[2])
            this->state[2]=false;
        else
            this->insertNewGyroData();

        if(this->state[3])
            this->state[3]=false;
        else
            this->insertNewWheelData();
    }
    else
        this->state[1]=true;
}

void RobotHistory::addNewGyroData(QVarLengthArray<float> data){
    this->insertNewGyroData(data);

    if(this->state[2]){
        if(this->state[0])
            this->state[0]=false;
        else
            this->insertNewLineData();

        if(this->state[1])
            this->state[1]=false;
        else
            this->insertNewAccelData();

        if(this->state[3])
            this->state[3]=false;
        else
            this->insertNewWheelData();
    }
    else
        this->state[2]=true;
}

void RobotHistory::addNewWheelData(QVarLengthArray<float> data){
    this->insertNewWheelData(data);

    if(this->state[3]){
        if(this->state[0])
            this->state[0]=false;
        else
            this->insertNewLineData();

        if(this->state[1])
            this->state[1]=false;
        else
            this->insertNewAccelData();

        if(this->state[2])
            this->state[2]=false;
        else
            this->insertNewGyroData();
    }
    else
        this->state[3]=true;
}
void RobotHistory::insertNewLineData(QVarLengthArray<bool> data){
    if(this->historyLine.length()==this->maxLength)
        this->historyLine.takeFirst();
    this->historyLine.append(data);
}

void RobotHistory::insertNewAccelData(QVarLengthArray<float> data){
    if(this->historyAccel.length()==this->maxLength)
        this->historyAccel.takeFirst();
    this->historyAccel.append(data);
}
void RobotHistory::insertNewGyroData(QVarLengthArray<float> data){
    if(this->historyGyro.length()==this->maxLength)
        this->historyGyro.takeFirst();
    this->historyGyro.append(data);
}
void RobotHistory::insertNewWheelData(QVarLengthArray<float> data){
    if(this->historyWheel.length()==this->maxLength)
        this->historyWheel.takeFirst();
    this->historyWheel.append(data);
}
