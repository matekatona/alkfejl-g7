#include "linesensor.h"

/*!
 * \brief LineSensor::LineSensor
 */
LineSensor::LineSensor()
    : AbstractSensor(27753)  // call superclass constructor with correct port number
{
    this->currentValues.clear();
}

/*!
 * \brief LineSensor::getValues
 * \return
 */
void
LineSensor::readSensor()
{
    while(!this->socket.canReadLine()){}

    QByteArray rawData = this->socket.readAll();
    QString rawString(rawData);

    QStringList rawValues = rawString.split(" ");
    this->currentValues.clear();
    for(uint i=0;i<21;i++)
        this->currentValues.append(rawValues[i].toFloat() < LINE_THRESHOLD);

    emit this->dataReady();
}

/*!
 * \brief LineSensor::isOk
 * \return
 */
QVarLengthArray<bool>
LineSensor::getCurrentValues()
{
    return this->currentValues;
}
