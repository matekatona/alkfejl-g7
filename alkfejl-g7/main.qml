import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "content"

Window {
    id: mainWindow;
    objectName: "mainWindow";
    visible: true
    minimumWidth: 900;
    minimumHeight: 700;

    property bool testPhase: true;
    property int angle: 0;
    property var sensors: [true, true, false, true, true, true, true, false, false, true, true, true, false, false, true, false, true, false, false, true, false];
    property bool temp;

    function test(){
        testTimer.running=true;
    }

    function timeTick(){
        if(mainWindow.testPhase){
            gyroX.setAngle(mainWindow.angle);
            gyroY.setAngle(mainWindow.angle);
            gyroZ.setAngle(mainWindow.angle);
            wheels.setAngle(mainWindow.angle);
            accelY.setAngle(mainWindow.angle);
        }
        else{
            gyroX.addAngle(-1);
            gyroY.addAngle(-1);
            gyroZ.addAngle(-1);
            wheels.addAngle(-1);
            accelY.addAngle(-1);
        }

        angle++;
        if(angle%10==0){
            lineSens.setValues(mainWindow.sensors);
            temp=mainWindow.sensors[0];
            mainWindow.sensors.shift();
            mainWindow.sensors[20]=temp;
        }

        if(mainWindow.angle>360){
            mainWindow.angle=0;
            if(mainWindow.testPhase){
                mainWindow.testPhase=false;
            }
            else{
                mainWindow.testPhase=true;
                testTimer.running=false;
            }
        }
    }

    Timer {
        id: testTimer;
        interval: 10; running: false; repeat: true;
        onTriggered: mainWindow.timeTick();
    }

    Rectangle {
        id: containerItem;
        anchors.fill: parent;
        color: "#E0E0E0"

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                lineSens.setValues(mainWindow.sensors);
                gyroX.addAngle(5);
                gyroY.addAngle(1);
                gyroZ.addAngle(11);
            }
        }

        GyroIndicator{
            id: gyroX;
            objectName: "gyroX";
            anchors.bottom: gyroY.top;
            anchors.right: parent.right;
            view: "front";
            angle: 45;
            title: "Front view";
        }

        GyroIndicator{
            id: gyroY;
            anchors.bottom: gyroZ.top;
            anchors.right: parent.right;
            view: "right";
            angle: -45;
            title: "Right view";
        }

        GyroIndicator{
            id: gyroZ;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;
            view: "top";
            angle: -45;
            title: "Top view";
        }

        GyroIndicator{
            id: wheels;
            anchors.left: parent.left;
            anchors.bottom: accelY.top;
            view: "top";
            angle: 15;
            title: "Wheels";
        }

        GyroIndicator{
            id: accelY;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            view: "top";
            angle: -20;
            title: "AccelY";
        }

        ColumnLayout{
            id: controlContainer;

            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.right: graphContainer.left;

            Rectangle{
                anchors.fill: parent;
                color: "black";
            }

            Button{
                id: buttonGUISelfTest;

                text: qsTr("GUI Self test");

                onClicked: {
                    testTimer.running=true;
                }
            }

            Button{

            }
        }

        ColumnLayout{
            id: graphContainer;

            anchors.top: parent.top;
            anchors.left: wheels.right;
            anchors.right: gyroZ.left;
            anchors.bottom: parent.bottom;

            Rectangle{
                anchors.fill: parent;
                color: "gray";
            }

            LedStrip{
                x:300;
                y:400;
                id: lineSens;
                anchors.top: parent.top;
                anchors.horizontalCenter: parent.horizontalCenter;
                stripLabel: "Line Sensor";
            }
        }
    }
}

