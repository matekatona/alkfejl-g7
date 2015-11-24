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
	LineSensor line;
	AccelSensor accel;
	GyroSensor gyro;
	WheelSensor wheels;
	CommandSocket command;
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
participant "GUI" as A;
participant "Robot" as B;
participant "Sensors/Command" as C;
participant "VREP" as D;
User -> A: Run;
activate A;
A -> B: run();
activate B
B -> C: commandRun%28%29;
activate C;
C -> D: TCPSocketSend%28%29;
deactivate A;
deactivate B;
deactivate C;
B -> C: line.getValues%28%29;
activate C;
C --> D: TCPSocketSend%28%29;
activate D;
D --> C: values;
deactivate D;
C --> B: values;
deactivate C;
@enduml
)

![Alt text](http://g.gravizo.com/g?
@startuml;
participant "Receive values" as A;
participant "Robot" as B;
participant "RobotHistory" as C;
participant "Plotter" as D;
A -> B: values;
B -> C: newValues%28%29;
C -> D: actualHistory%28%29;
activate D;
D -> D: graph%28%29;
activate D;
deactivate D;
D --> C: endGraph;
deactivate D;
@enduml
)