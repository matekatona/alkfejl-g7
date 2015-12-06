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
 * \brief LineSensor::isOk
 * \return
 */
QVarLengthArray<bool>
LineSensor::getBools()
{
    QVarLengthArray<bool> vals;
    this->getValues();
    for(uint i=0;i<21;i++)
        vals.insert(i, this->currentValues.at(i) < LINE_THRESHOLD);
    return vals;
}

/*!
 * \brief LineSensor::getValues
 * \return
 */
QVarLengthArray<float>
LineSensor::getValues()
{
    QString raw = this->readSensor();
    if(raw == "ERROR")
    {
        throw std::runtime_error("this is not really a runtime error");
    }
    QStringList rawValues = raw.split(QRegExp("\\s"));
    for(uint i=0;i<21;i++)
        this->currentValues.insert(i, rawValues[i].toFloat());
    return this->currentValues;
}
