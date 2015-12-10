//! \file 
//! \brief This file contains the LineSensor class.

#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "simcomm.h"

#define LINE_THRESHOLD 0.5f

/*!
 * \brief This class is for reading the values of the line sensor of the robot.
 */

class LineSensor : public SimComm
{
    Q_OBJECT
public:
    LineSensor();
    QVarLengthArray<bool> getValues();
};

#endif // LINESENSOR_H
