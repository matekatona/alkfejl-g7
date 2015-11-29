import QtQuick 2.0

Item {
    id: ledStrip;
    width: 420;
    height: 48;

    property var ledValues: [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];
    property alias stripLabel: label.text;

    function setValues(values){
        ledStrip.ledValues=values;
    }

    Item {
        id: leds;
        width: 420;
        height: 18;
        anchors.bottom: parent.bottom;

        Repeater {
            model: 21;
            Image {
                x:index*20;
                source: "led_on.png"
                visible: ledStrip.ledValues[index];
            }
        }
        Repeater {
            model: 21;
            Image {
                x:index*20;
                source: "led_off.png"
                visible: !ledStrip.ledValues[index];
            }
        }
    }

    Text {
        id: label;
        y: 10;
        anchors.horizontalCenter: leds.horizontalCenter;
        color:"black";
        font.pixelSize: 14;
        style: Text.Raised;
        styleColor: "black";
    }
}

