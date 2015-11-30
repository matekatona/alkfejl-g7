import QtQuick 2.0

Item {
    id: alertLamp;
    width: 70;
    height: 100;

    property bool alert: false;
    property alias alertLabel: label.text;

    function setAlert(values){
        alertLamp.alert=values;
    }

    Item{
        id: alertImage;
        width: 70;
        height: 70;
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
        font.pixelSize: 16;
        style: Text.Raised;
        styleColor: "black";
    }
}

