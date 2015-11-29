import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import Graph 1.0
import "content"

Window {
    id: mainWindow;
    objectName: "mainWindow";
    visible: true
    minimumWidth: 900;
    minimumHeight: 700;

    property bool testPhase: true;
    property int angle: 0;
    property var sensorsInit: [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];
    property var sensors: sensorsInit.slice();
   property bool temp;

    property real graphHeight: 250;
    property real graphMargin: 10;

    property real buttonMargin: 20;

    property real tableHeight: 35;

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

        if(mainWindow.angle>260)
            speedGraph.newSample(0.5-10/480);
        else
            speedGraph.newSample(0.5-10/480+Math.sin(mainWindow.angle/22.5 * Math.PI * 2)*0.5);

        angle++;
        if(angle%10==0){
            lineSens.setValues(mainWindow.sensors);
            temp=mainWindow.sensors[11];
            mainWindow.sensors.shift();
            mainWindow.sensors[20]=!temp;

            alertLamp.alert=!alertLamp.alert;
        }

        if(mainWindow.angle>360){
            mainWindow.angle=0;
            if(mainWindow.testPhase){
                mainWindow.testPhase=false;
            }
            else{
                mainWindow.testPhase=true;
                testTimer.running=false;
                lineSens.setValues(mainWindow.sensorsInit);
                alertLamp.alert=false;
            }
        }
    }

    Timer {
        id: testTimer;
        interval: 10; running: false; repeat: true;
        onTriggered: {
            mainWindow.timeTick();
        }
    }

    Rectangle {
        id: containerItem;
        anchors.fill: parent;
        color: "#E0E0E0"

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
            anchors.margins: mainWindow.buttonMargin;

            Button{
                id: buttonGUISelfTest;
                implicitWidth: 150;
                implicitHeight: 50;
                anchors.horizontalCenter: parent.horizontalCenter;
                text: qsTr("GUI Self test");

                onClicked: {
                    testTimer.running=true;
                }
            }

            AlertLamp{
                id: alertLamp;
                objectName: "alertLamp";
                anchors.horizontalCenter: parent.horizontalCenter;
                alertLabel: "Line lost";
                alert: true;
            }
        }

        ColumnLayout{
            id: graphContainer;

            anchors.top: parent.top;
            anchors.left: wheels.right;
            anchors.right: gyroZ.left;
            anchors.bottom: parent.bottom;

            LedStrip{
                id: lineSens;
                x:300;
                y:400;
                anchors.top: parent.top;
                anchors.horizontalCenter: parent.horizontalCenter;
                stripLabel: "Line Sensor";
            }

            Item{
                id: dataContainer;
                anchors.top: lineSens.bottom;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.bottom: graphBorder.top;

                GridLayout{
                    anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.verticalCenter: parent.verticalCenter;

                    columns: 5;

                    Text{
                        text: "Acceleration X:";
                    }
                    Text{
                        id: textAccelX;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Text{
                        text: "Current status:";
                    }
                    Text{
                        id: textCurStatus;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Text{
                        text: "Acceleration Y:";
                    }
                    Text{
                        id: textAccelY;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Text{
                        text: "Set status:";
                    }
                    ComboBox{
                        id: comboSetStatus;
                        model: ["Run", "Stop"];
                    }

                    Text{
                        text: "Acceleration Z:";
                    }
                    Text{
                        id: textAccelZ;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Button{
                        id: buttonStatusSend;
                        text: "Send";
                        Layout.columnSpan: 2;
                        anchors.right: parent.right;
                    }

                    Text{
                        text: "Gyroscope X:";
                    }
                    Text{
                        id: textGyroX;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Text{
                        text: "Current speed:";
                    }
                    Text{
                        id: textCurSpeed;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Text{
                        text: "Gyroscope Y:";
                    }
                    Text{
                        id: textGyroY;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Text{
                        text: "Set speed:";
                    }
                    TextField{
                        id: editSetSpeed;
                        text: "0,4";
                        implicitWidth: comboSetStatus.width;
                    }

                    Text{
                        text: "Gyroscope Z:";
                    }
                    Text{
                        id: textGyroZ;
                        text: "UNKNOWN";
                        color: "gray";
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Button{
                        id: buttonSpeedSend;
                        text: "Send";
                        Layout.columnSpan: 2;
                        anchors.right: parent.right;
                    }
                }
            }

            Rectangle {
                id: graphBorder;
                height: mainWindow.graphHeight+mainWindow.graphMargin;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;
                anchors.margins: mainWindow.graphMargin/2;
                border.width: mainWindow.graphMargin/2;
                border.color: "gray";
            }

            Graph {
                id: speedGraph;
                objectName: "speedGraph";
                height: mainWindow.graphHeight;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;
                anchors.margins: mainWindow.graphMargin;


                function newSample(i) {
                    speedGraph.removeFirstSample();
                    speedGraph.appendSample(i);
                }

                Component.onCompleted: {
                    for (var i=0; i<100; ++i)
                        appendSample(0);
                }

                property int offset: 100;
            }

            Text{
                anchors.bottom: graphBorder.top;
                anchors.margins: mainWindow.graphMargin;
                text: "Speed [1m/s/div]";
            }
        }
    }
}

