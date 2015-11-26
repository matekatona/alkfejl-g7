import QtQuick 2.3
import QtQuick.Window 2.2
import "content"

Window {
    visible: true
    width:400*2;
    height: 280*2;

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            var sensors= [true, true, false, false, true, true, true, false, false, true, true, true, false, false, true, true, true, false, false, true, false];
            lineSens.setValues(sensors);
            test.setAngle(20);
            test2.addAngle(1);
        }
    }

    GyroIndicator{
        id: test;
        anchors.left: parent;
        view: "right";
        angle: 45;
        title: "Right view";
    }

    GyroIndicator{
        id: test2;
        anchors.left: test.right;
        view: "right";
        angle: -45;
        title: "Right view";
    }

    LedStrip{
        x:300;
        y:400;
        id: lineSens;
        anchors.top: test.bottom;
        stripLabel: "Line Sensor";
    }
}

