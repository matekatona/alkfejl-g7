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
AlarmGenerator::setLineState(QVarLengthArray<bool> l)
{
    bool oneofthem;

    this->lineFound = false;

    if(l.size() > 0)
        oneofthem = l[0];
    else
        return;

    for(quint8 i = 1 ; i < l.size() ; i++)
    {
        if(l[i] != oneofthem)
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
 * \brief AlarmGenerator::updateColor
 */
void AlarmGenerator::updateColor()
{
    if(socketsConnected)
    {
        if(lineFound)
        {
            this->color = ALARM_GREEN;
        }
        else
        {
            this->color = ALARM_RED;
        }
    }
    else
    {
        this->color = ALARM_YELLOW;
    }
}

/*!
 * \brief AlarmGenerator::updateAlarm updates LED on GUI to current color
 *
 * Emits the `setAlarm()` signal with the color as paramter. The color is
 * determined by the previously set states in `updateColor()`.
 * \see the slot to which this signal is connected
 * \see AlarmGenerator::updateColor()
 */
void
AlarmGenerator::updateAlarm()
{
    emit this->setAlarm(this->color);
}

/*!
 * \brief AlarmGenerator::getColor
 * \return
 */
int
AlarmGenerator::getColor()
{
    return this->color;
}
