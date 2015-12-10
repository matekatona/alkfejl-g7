#include "linesensor.h"

/*!
 * \brief LineSensor::LineSensor creates sensor object, that is connected to
 *                               the linesensor port of VREP
 *
 * No detailed description is available, sorry about that.
 */
LineSensor::LineSensor() :
    SimComm(PORT_NUM_LINE)  // call superclass constructor with correct port number
{
    this->cachevalues = this->pvalues;
    this->pvalues.reset();

    QObject::connect(this, SIGNAL(cache_expired()), this, SLOT(reset_cache()));
}

/*!
 * \brief AccelSensor::clear_cache delete cached sensor values
 *
 * The next sensor read will result in reading new values from VREP
 * \see SimComm::cache_expired
 */
void
LineSensor::reset_cache()
{
    this->pvalues.reset();
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
    QVarLengthArray<bool> vals;
    for(quint8 i=0;i<21;i++)
        vals.append(false);

    // check for value in cache
    std::shared_ptr<QVarLengthArray<bool>> cvalues = this->cachevalues.lock();
    if(cvalues)
    {
        // use cached value
        vals = *cvalues;
    }
    else
    {
        // read new values
        QString raw = this->read();
        if(raw.length() < 100)
            return vals;
        QStringList rawValues = raw.split(QRegExp("\\s"));
        if(rawValues.size() < 21)
            return vals;

        for(quint8 i=0;i<rawValues.size();i++)
            if(i<vals.size()) vals.replace(i, rawValues[i].toFloat() < LINE_THRESHOLD);
            else vals.append(rawValues[i].toFloat() < LINE_THRESHOLD);

        // cache values
        this->pvalues = std::make_shared<QVarLengthArray<bool>>(vals);
        this->cachevalues = this->pvalues;
        this->start_cache_timer();  // will reset cache 70ms later
    }

    return vals;
}
