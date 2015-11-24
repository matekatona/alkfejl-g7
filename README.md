![Alt text](http://g.gravizo.com/g?
/**
*Abstract Sensor
*@opt all
*/
class AbstractSensor{
    QTCPSocket commSock;
    public int readSensor%28%29;
}
/**
*LineSensor
*@opt all
*/
class LineSensor extends AbstractSensor {
        float[] sensorValues;
        public bool isOk%28%29;
        public int getValues%28float[] values%29;
}
/**
*AccelSensor
*@opt all
*/
class AccelSensor extends AbstractSensor {
        float[] sensorValues;
        public float getX%28%29;
        public float getY%28%29;
        public float getZ%28%29;
}
/**
*GyroSensor
*@opt all
*/
class GyroSensor extends AbstractSensor {
        float[] sensorValues;
        public float getX%28%29;
        public float getY%28%29;
        public float getZ%28%29;
}
/**
*WheelSensor
*@opt all
*/
class WheelSensor extends AbstractSensor {
        float[] sensorValues;
        public float getLeft%28%29;
        public float getRight%28%29;
})

![Alt text](http://g.gravizo.com/g?
/**
*Command Socket
*@opt all
*/
class CommandSocket{
    QTCPSocket commSock;
    public int connect%28%29;
    public int disconnect%28%29;
    public int getStatus%28%29;
    public int run%28%29;
    public int stop%28%29;
    public int getSpeed%28%29;
    public int setSpeed%28%29;
})

![Alt text](http://g.gravizo.com/g?
/**
*Robot
*@opt all
*@composed 1..* LineSensor
*@composed 1..* AccelSensor
*@composed 1..* GyroSensor
*@composed 1 CommandSocket
*/
class Robot{
})

![Alt text](http://g.gravizo.com/g?
/**
*RobotHistory
*@opt all
*@assoc Plotter
*/
class RobotHistory{
	List speedHistory;
	List statusHistory;
	signal historyChanged%28%29;
}
/**
*Plotter
*@opt all
*/
class Plotter{
	slot graph%28%29;
})

![Alt text](http://g.gravizo.com/g?
@startuml;
actor User;
participant "First Class" as A;
participant "Second Class" as B;
participant "Last Class" as C;
User -> A: DoWork;
activate A;
A -> B: Create Request;
activate B;
B -> C: DoWork;
activate C;
C --> B: WorkDone;
destroy C;
B --> A: Request Created;
deactivate B;
A --> User: Done;
deactivate A;
@enduml
)

![Alt text](http://g.gravizo.com/g?
/**
 * Associations with visibility
 * UML User Guide p. 145
 *
 * @opt horizontal
 * @hidden
 */
class UMLOptions {}

/** @assoc * - "*\n\n+user " User */
class UserGroup {}

/** @navassoc "1\n\n+owner\r" - "*\n\n+key" Password */
class User{}

class Password{}
)