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
            speedGraph.newSample(0.5);
        else
            speedGraph.newSample(0.5+Math.sin(mainWindow.angle/22.5 * Math.PI * 2)*0.5);

        angle++;
        if(angle%10==0){
            lineSens.setValues(mainWindow.sensors);
            temp=mainWindow.sensors[11];
            mainWindow.sensors.shift();
            mainWindow.sensors[20]=!temp;

            alertLamp.alert=(alertLamp.alert+1)%3;

            textAccelX.setValue(angle);
            textAccelY.setValue(angle);
            textAccelZ.setValue(angle);
            textGyroX.setValue(angle);
            textGyroY.setValue(angle);
            textGyroZ.setValue(angle);
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
                alertLamp.alert=1;
                textAccelX.setValue("UNKNOWN");
                textAccelY.setValue("UNKNOWN");
                textAccelZ.setValue("UNKNOWN");
                textGyroX.setValue("UNKNOWN");
                textGyroY.setValue("UNKNOWN");
                textGyroZ.setValue("UNKNOWN");
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
            objectName: "carGyroX";
            anchors.bottom: gyroY.top;
            anchors.right: parent.right;
            view: "front";
            title: "Front view";
        }

        GyroIndicator{
            id: gyroY;
            objectName: "carGyroY";
            anchors.bottom: gyroZ.top;
            anchors.right: parent.right;
            view: "right";
            title: "Right view";
        }

        GyroIndicator{
            id: gyroZ;
            objectName: "carGyroZ";
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;
            view: "top";
            title: "Top view";
        }

        GyroIndicator{
            id: wheels;
            objectName: "wheels";
            anchors.left: parent.left;
            anchors.bottom: accelY.top;
            view: "top";
            title: "Wheels";
        }

        GyroIndicator{
            id: accelY;
            objectName: "carAccelY"
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            view: "top";
            title: "AccelY";
        }

        ColumnLayout{
            id: leftControlContainer;

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

            Button{
                id: buttonCarSelfTest;
                objectName: "buttonCarSelfTest";
                implicitWidth: 150;
                implicitHeight: 50;
                anchors.horizontalCenter: parent.horizontalCenter;
                text: qsTr("Car Self Test");
            }

            AlertLamp{
                id: alertLamp;
                objectName: "alertLamp";
                anchors.horizontalCenter: parent.horizontalCenter;
                alertLabel: "Line lost";
                alert: 1;
            }
        }

        ColumnLayout{
            id: rightControlContainer;

            anchors.top: parent.top;
            anchors.left: graphContainer.left;
            anchors.margins: mainWindow.buttonMargin;

        }

        ColumnLayout{
            id: graphContainer;

            anchors.top: parent.top;
            anchors.left: wheels.right;
            anchors.right: gyroZ.left;
            anchors.bottom: parent.bottom;

            LedStrip{
                id: lineSens;
                objectName: "lineSens";
                x:300;
                y:400;
                anchors.top: parent.top;
                anchors.horizontalCenter: parent.horizontalCenter;
                stripLabel: "Line Sensor";
            }

            Button{
                id: buttonConDiscon;
                objectName: "buttonConDiscon";
                anchors.top: lineSens.bottom;
                anchors.horizontalCenter: lineSens.horizontalCenter;
                anchors.margins: mainWindow.buttonMargin;
                implicitWidth: 150;
                text: "Connect";
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

                    KeyValuePair{
                        id: textAccelX;
                        objectName: "textAccelX";
                        key: "Acceleration X:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    KeyValuePair{
                        id: textCurStatus;
                        objectName: "textCurStatus"
                        key: "Current status:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    KeyValuePair{
                        id: textAccelY;
                        objectName: "textAccelY";
                        key: "Acceleration Y:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Text{
                        text: "Set status:";
                        Layout.alignment: Qt.AlignTop;
                    }
                    ComboBox{
                        id: comboSetStatus;
                        objectName: "comboSetStatus";
                        Layout.alignment: Qt.AlignRight;
                        model: ["Run", "Stop"];
                    }

                    KeyValuePair{
                        id: textAccelZ;
                        objectName: "textAccelZ";
                        key: "Acceleration Z:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Button{
                        id: buttonSendStatus;
                        objectName: "buttonSendStatus";
                        text: "Send";
                        Layout.columnSpan: 2;
                        Layout.alignment: Qt.AlignLeft;
                    }

                    KeyValuePair{
                        id: textGyroX;
                        objectName: "textGyroX";
                        key: "Gyroscope X:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    KeyValuePair{
                        id: textCurSpeed;
                        objectName: "textCurSpeed";
                        key: "Current speed:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    KeyValuePair{
                        id: textGyroY;
                        objectName: "textGyroY";
                        key: "Gyroscope Y:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Text{
                        text: "Set speed:";
                        Layout.alignment: Qt.AlignTop;
                    }
                    TextField{
                        id: editSetSpeed;
                        objectName: "editSetSpeed";
                        Layout.alignment: Qt.AlignRight;
                        text: "0,4";
                        implicitWidth: comboSetStatus.width;
                    }

                    KeyValuePair{
                        id: textGyroZ;
                        objectName: "textGyroZ";
                        key: "Gyroscope Z:"
                        value: "UNKNOWN";
                        height: mainWindow.tableHeight;

                        Layout.columnSpan: 2;
                    }

                    Item{
                        implicitWidth: dataContainer.width*0.1;
                        implicitHeight: mainWindow.tableHeight;
                    }

                    Button{
                        id: buttonSendSpeed;
                        objectName: "buttonSendSpeed";
                        text: "Send";
                        Layout.columnSpan: 2;
                        Layout.alignment: Qt.AlignLeft;
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
                    speedGraph.appendSample(i-10/480);
                }

                Component.onCompleted: {
                    for (var i=0; i<100; ++i)
                        appendSample(0.5-10/480);
                }

                property int offset: 100;
            }

            Text{
                anchors.bottom: graphBorder.top;
                anchors.margins: mainWindow.graphMargin;
                text: "Speed [0.3m/s/div]";
            }
        }
    }
}

