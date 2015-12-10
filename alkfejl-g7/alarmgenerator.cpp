#include "alarmgenerator.h"

/*!
 * \brief This is the constructor of AlarmGenerator.
 */
AlarmGenerator::AlarmGenerator()
{
    this->socketsConnected = false;
    this->lineFound = false;
}

/*!
 * \brief AlarmGenerator::setLineState determines line _foundness_. \n
 *
 *                                     TODO: introduce the word _foundness_ to the English language.
 *
 * If all values are the same, sets `lineFound` to `false`, otherwise to `true`
 * \param lineVals line sensor values read from line sensor
 */
void
AlarmGenerator::setLineState(QVarLengthArray<bool> lineVals)
{
    bool oneofthem;

    this->lineFound = false;

    if(lineVals.size() > 0)
        oneofthem = lineVals[0];
    else
        return;

    for(quint8 i = 1 ; i < lineVals.size() ; i++)
    {
        if(lineVals[i] != oneofthem)
        {
            this->lineFound = true;
            return;
        }
    }
}

/*!
 * \brief AlarmGenerator::setConnectionState determines socket connectedness. \n
 *
 *                                           TODO: introduce the word _connectedness_ to the English language.
 *
 * If all sockets are connected, sets `isConnected` to `true`, otherwise to `false`
 * \param isConnected AND of all socket connection states
 */
void
AlarmGenerator::setConnectionState(bool isConnected)
{
    this->socketsConnected = isConnected;
}

/*!
 * \brief AlarmGenerator::updateAlarm updates LED on GUI according to states
 *
 * Emits the `setAlarm()` signal with the color as paramter. The color is
 * determined by the previously set states.
 * \see setAlarm signal 
 */
void
AlarmGenerator::updateAlarm()
{
    if(socketsConnected)
    {
        if(lineFound)
        {
            emit this->setAlarm(ALARM_GREEN);
        }
        else
        {
            emit this->setAlarm(ALARM_RED);
        }
    }
    else
    {
        emit this->setAlarm(ALARM_YELLOW);
    }
}
