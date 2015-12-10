# UML diagram for Alkfejl-g7

![Alt text](http://g.gravizo.com/g?
class QObject {}
class Robot extends QObject {}
class AlarmGenerator extends QObject {}
class SimComm extends QObject {}
class GuiHandler extends QObject {}
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
class SimComm extends QObject{
    QTCPSocket socket;
    protected QString read%28%29;
    protected void write%28QString cmd%29;
    public void connect%28%29;
    public void disconnect%28%29;
    public bool isConnected%28%29;
}
/**
*LineSensor
*@opt all
*/
class LineSensor extends SimComm {
	bool[] values;
    public QVarLengthArray getValues%28%29;
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
    public QVarLengthArray getWheels%28%29;
}
/**
*RobotControl
*@opt all
*/
class RobotControl extends SimComm {
  float speed;
  QString status;
	public QString getStatus%28%29;
	public void setStatus%28QString status%29;
	public float getSpeed%28%29;
	public void setSpeed%28float speed%29;
}
/**
*AlarmGenerator
*@opt all
*/
class AlarmGenerator extends QObject {
    int color;
    void setLineState%28QVarLengthArray lineVals%29;
    void setConnectionState%28bool connectionState%29;
    void updateColor%28%29;
    int getColor%28%29;
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
*@composed 1..* AlarmGenerator
*/
class Robot{
	LineSensor line;
	AccelSensor accel;
	GyroSensor gyro;
	WheelSensor wheels;
	RobotControl control;
  AlarmGenerator alarmgen;
})


### Sequence diagram

![Alt text](http://g.gravizo.com/g?
@startuml;
actor User;
participant "GUI" as A;
participant "GuiHandler" as A2;
participant "Robot" as B;
participant "Sensors/Command" as C;
participant "VREP" as D;
User -> A: Run;
activate A;
A -> A2: runButtonClicked;
activate A2;
A2 -> B: signal run%28%29;
activate B;
B -> C: control.setStatus%28%29;
activate C;
C -> D: socket.write%28%29;
deactivate A;
deactivate A2;
deactivate B;
deactivate C;
B -> B: update signal;
activate B;
B -> C: sensors.get%28%29;
activate C;
C -> D: socket.write%28%22GET%22%29;
activate D;
D --> C: socket.read%28%29;
deactivate D;
C --> B: values;
deactivate C;
B --> A2: signals setValue%28%29;
activate A2;
A2 -> A: updateGUI;
deactivate A2;
deactivate B;
A -> User: happiness;
@enduml
)

### Car self test

![Alt text](http://g.gravizo.com/g?
@startuml;
actor User;
participant "GUI" as A;
participant "GuiHandler" as A2;
participant "Robot" as B;
participant "Sensors/Command" as C;
participant "VREP" as D;
User -> A: Car self test;
activate A;
A -> A2: buttonCarSelfTestClicked%28%29;
activate A2;
A2 -> B: signal selfTest%28%29;
activate B;
B -> C: setStatus%28%22Run%22%29;
activate C;
C -> D: socket.write%28%29;
deactivate C;
B -> B: test_timer.start%28%29;
deactivate A;
deactivate A2;
deactivate B;
B -> B: signal timeout%28%29;
activate B;
B -> C: setSpeed%28speed%29;
activate C;
C -> D: socket.write%28%29;
deactivate C;
B -> B: test_timer.start%28%29;
deactivate B;
B -> B: signal timeout%28%29;
activate B;
B -> C: setSpeed%280%29;
activate C;
C -> D: socket.write%28%29;
deactivate C;
B -> B: test_timer.start%28%29;
deactivate B;
B -> B: signal timeout%28%29;
activate B;
B -> C: setSpeed%28speed%29;
activate C;
C -> D: socket.write%28%29;
deactivate C;
B -> C: setStatus%28%22Run%22%29;
activate C;
C -> D: socket.write%28%29;
deactivate C;
B -> B: test_timer.start%28%29;
deactivate B;
B -> B: timeout%28%29;
activate B;
B -> C: setStatus%28%22Stop%22%29;
activate C;
C -> D: socket.write%28%29;
deactivate C;
B -> B: test_timer.start%28%29;
deactivate B;
B -> B: timeout%28%29;
activate B;
B -> B:test_timer.reset%28%29;
deactivate B;
A -> User: happiness;
@enduml
)
