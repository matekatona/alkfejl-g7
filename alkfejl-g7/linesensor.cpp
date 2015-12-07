#include "linesensor.h"

/*!
 * \brief LineSensor::LineSensor
 */
LineSensor::LineSensor()
    : AbstractSensor(27753)  // call superclass constructor with correct port number
{
    // nothing
}

/*!
 * \brief LineSensor::getValues
 * \return
 */
QVarLengthArray<bool>
LineSensor::getValues()
{
    QVarLengthArray<bool> vals(21);
    QString raw = this->readSensor();
    QStringList rawValues = raw.split(QRegExp("\\s"));
    for(quint8 i=0;i<rawValues.size();i++)
        vals.insert(i, rawValues[i].toFloat() < LINE_THRESHOLD);
    return vals;
}
