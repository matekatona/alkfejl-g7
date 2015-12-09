#include "alarmgenerator.h"


/*!
 * \brief AlarmGenerator::AlarmGenerator this class handles the alarm on the GUI
 *
 * Based on two parameters, the class sets the color o the LED in the GUI. The
 * colors are as following:
 *      YELLOW -> if not all sockets are connected
 *      RED    -> if all sockets are connected, but no line is found
 *      GREEN  -> if all sockets are connected, and a line is found
 * Wether a line is found or not is determined by the linesensor values: if all
 * values are the same, then no line is present, otherwise there is one.
 */
AlarmGenerator::AlarmGenerator()
{
    this->socketsConnected = false;
    this->lineFound = false;
}

/*!
 * \brief AlarmGenerator::setLineState determines line _foundness_
 *                                     TODO: introduce this word to the English language
 *
 * If all values are the same, sets `lineFound` to `false`, otherwise to `true`
 * \param lineVals linesensor values read from linesensor
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
 * \brief AlarmGenerator::setConnectionState determines socket connectedness
 *                                           TODO: introduce this word to the English language
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
 * \see the slot to which this signal is connected
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