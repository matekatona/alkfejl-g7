# UML diagram for Alkfejl-g7

![Alt text](http://g.gravizo.com/g?
class SimComm {}
class Robot {}
class RobotControl extends SimComm {}
class AccelSensor extends SimComm {}
class GyroSensor extends SimComm {}
class LineSensor extends SimComm {}
class WheelSensor extends SimComm {}
)

## Detailed UML diagrams

![Alt text](http://g.gravizo.com/g?
/**
*SimComm
*@opt all
*/
class SimComm{
    QTCPSocket socket;
    protected QString read%28%29;
    protected void write%28%29;
    public void connect%28%29;
    public void disconnect%28%29;
}
/**
*LineSensor
*@opt all
*/
class LineSensor extends SimComm {
	bool[] values;
    public bool[] getValues%28%29;
}
/**
*AccelSensor
*@opt all
*/
class AccelSensor extends SimComm {
    float[] values;
    public float getX%28%29;
    public float getY%28%29;
    public float getZ%28%29;
}
/**
*GyroSensor
*@opt all
*/
class GyroSensor extends SimComm {
    float[] values;
    public float getX%28%29;
    public float getY%28%29;
    public float getZ%28%29;
}
/**
*WheelSensor
*@opt all
*/
class WheelSensor extends SimComm {
    float[] values;
    public float getLeft%28%29;
    public float getRight%28%29;
}
/**
*RobotControl
*@opt all
*/
class RobotControl extends SimComm {
	float speed;
	QString status;
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
*@composed 1..* RobotControl
*/
class Robot{
	LineSensor line;
	AccelSensor accel;
	GyroSensor gyro;
	WheelSensor wheels;
	RobotControl control;
})

### Sequence diagram

![Alt text](http://g.gravizo.com/g?
@startuml;
actor User;
participant "GUI" as A;
participant "Robot" as B;
participant "Sensors/Command" as C;
participant "VREP" as D;
User -> A: Run;
activate A;
A -> B: run signal;
activate B;
B -> C: control.run%28%29;
activate C;
C -> D: socket.send%28%29;
deactivate A;
deactivate B;
deactivate C;
A -> B: update signal;
activate B;
B -> C: sensors.get%28%29;
activate C;
C --> D: socket.send%28%29;
activate D;
D --> C: socket.read%28%29;
deactivate D;
C --> B: values;
deactivate C;
B -> A: setValue signals;
deactivate B;
@enduml
)
