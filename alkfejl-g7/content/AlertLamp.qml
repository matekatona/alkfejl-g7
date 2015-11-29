import QtQuick 2.0

Item {
    id: alertLamp;
    width: 100;
    height: 150;

    property bool alert: false;
    property alias alertLabel: label.text;

    function setValue(values){
        alertLamp.alert=values;
    }

    Item{
        id: alertImage;
        width: 100;
        height: 100;
        anchors.bottom: parent.bottom;

        Image {
            source: "alert_on.png"
            visible: alert;
        }

        Image {
            source: "alert_off.png"
            visible: !alert;
        }
    }

    Text {
        id: label;
        y: 10;
        anchors.horizontalCenter: alertImage.horizontalCenter;
        color:"black";
        font.pixelSize: 24;
        style: Text.Raised;
        styleColor: "black";
    }
}

