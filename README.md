# UML diagram for Alkfejl-g7

![Alt text](http://g.gravizo.com/g?
class VREPComm{}
class Robot extends VREPComm {}
class AbstractSensor extends VREPComm {}
class AccelSensor extends AbstractSensor {}
class GyroSensor extends AbstractSensor {}
class LineSensor extends AbstractSensor {}
)

## Other sample UML diagrams

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
