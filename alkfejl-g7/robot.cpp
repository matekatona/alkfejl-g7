#include "robot.h"

Robot::Robot()
{

}

void Robot::init()
{
    connect(25455);
    linesens.connect(27753);
    accel.connect(24931);
    gyro.connect(26489);
}

