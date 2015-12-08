# UML diagram for Alkfejl-g7

![Alt text](http://g.gravizo.com/g?
class Robot {}
class AbstractSensor {}
class AccelSensor extends AbstractSensor {}
class GyroSensor extends AbstractSensor {}
class LineSensor extends AbstractSensor {}
class WheelSensor extends AbstractSensor {}
)

## Detailed UML diagrams

![Alt text](http://g.gravizo.com/g?
/**
*Abstract Sensor
*@opt all
*/
class AbstractSensor{
    QTCPSocket commSock;
    protected int readSensor%28%29;
}
/**
*LineSensor
*@opt all
*/
class LineSensor extends AbstractSensor {
        public bool[] getValues%28%29;
        public void connect%28%29;
        public void disconnect%28%29;
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
    public void connect%28%29;
    public void disconnect%28%29;
    public QString getStatus%28%29;
    public void setStatus%28%29;
    public float getSpeed%28%29;
    public void setSpeed%28%29;
})

![Alt text](http://g.gravizo.com/g?
/**
*Robot
*@opt all
*@composed 1..* LineSensor
*@composed 1..* AccelSensor
*@composed 1..* GyroSensor
*@composed 1..* WheelSensor
*@composed 1 CommandSocket
*/
class Robot{
	LineSensor line;
	AccelSensor accel;
	GyroSensor gyro;
	WheelSensor wheels;
	CommandSocket cmd;
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
A -> B: run%28%29;
activate B;
B -> C: command.run%28%29;
activate C;
C -> D: TCPSocket.send%28%29;
deactivate A;
deactivate B;
deactivate C;
A -> B: update%28%29;
activate B;
B -> C: sensors.getValue%28%29;
activate C;
C --> D: TCPSocket.send%28%29;
activate D;
D --> C: values;
deactivate D;
C --> B: values;
deactivate C;
deactivate B;
B -> A: setValues%28%29;
@enduml
)
