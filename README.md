![Alt text](http://g.gravizo.com/g?
/**
*Abstract Sensor
*@opt all
*/
class AbstractSensor{
    public QTCPSocket commSock;
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
*Structural Things
*@opt commentname
*@note Notes can
*be extended to
*span multiple lines
*/
class Structural{}
/**
*@opt all
*@note Class
*/
class Counter extends Structural {
        static public int counter;
        public int getCounter%28%29;
}
/**
*@opt shape activeclass
*@opt all
*@note Active Class
*/
class RunningCounter extends Counter{}
)
