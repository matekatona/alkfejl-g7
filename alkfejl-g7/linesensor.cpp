#include "linesensor.h"

/*!
 * \brief LineSensor::LineSensor creates sensor object, that is connected to
 *        the linesensor port of VREP.
 */
LineSensor::LineSensor() :
    SimComm(PORT_NUM_LINE)  // call superclass constructor with correct port number
{
    // nothing
}

/*!
 * \brief LineSensor::getValues get state of all 21 line sensors
 *
 * This function reads the line sensor values, and compares them to LINE_THRESHOLD
 * defined in `linesensor.h`. If a value is lower than the threshold, it is
 * considered to be over the line (the line is dark), and has the value `true`,
 * otherwise it's `false`.
 * \see SimComm::read
 * \return bool array of sensor values
 */
QVarLengthArray<bool>
LineSensor::getValues()
{
    QVarLengthArray<bool> vals(21);
    QString raw = this->read();
    QStringList rawValues = raw.split(QRegExp("\\s"));
    for(quint8 i=0;i<rawValues.size();i++)
        vals.insert(i, rawValues[i].toFloat() < LINE_THRESHOLD);
    return vals;
}
