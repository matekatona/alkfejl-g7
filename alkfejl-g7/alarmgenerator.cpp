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
 * \brief AlarmGenerator::updateColor
 *
 *
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
 * \brief AlarmGenerator::updateAlarm updates LED on GUI to current color.
 *
 * Emits the `setAlarm()` signal with the color as parameter. The color is
 * determined by the previously set state.
 * \see setAlarm signal
 * \see AlarmGenerator::updateColor
 */
void
AlarmGenerator::updateAlarm()
{
    this->updateColor();
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

