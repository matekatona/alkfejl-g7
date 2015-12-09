#include "linesensor.h"

/*!
 * \brief The constructor of LineSensor.
 * It initializes communication with the sensor over the TCP port defined in PORT_NUM_LINE.
 * \sa PORT_NUM_LINE
  */
LineSensor::LineSensor() :
    SimComm(PORT_NUM_LINE)  // call superclass constructor with correct port number
{
    // nothing
}

/*!
 * \brief It reads 21 values from the real line sensor over TCP.
 * \return 21 boolean values in a QVarLengthArray.
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
