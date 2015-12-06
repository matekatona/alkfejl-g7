#include "linesensor.h"

/*!
 * \brief LineSensor::LineSensor
 */
LineSensor::LineSensor()
    : AbstractSensor(27753)  // call superclass constructor with correct port number
{
    float buf[21] = {.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0};
    QVarLengthArray<float> def_vals;
    this->currentValues.append(buf, 21);
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
        vals.append(this->currentValues.at(i) < LINE_THRESHOLD);
    return vals;
}

/*!
 * \brief LineSensor::getValues
 * \return
 */
QVarLengthArray<float>
LineSensor::getValues()
{
    float buf[21] = {.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0};
    QVarLengthArray<float> def_vals;
    def_vals.append(buf, 21);

    QString raw = this->readSensor();
    if(raw.length() < 10)
    {
        return def_vals;
    }
    QStringList rawValues = raw.split(QRegExp("\\s"));
    for(uint i=0;i<rawValues.size();i++)
        this->currentValues.insert(i, rawValues[i].toFloat());
    return this->currentValues;
}
