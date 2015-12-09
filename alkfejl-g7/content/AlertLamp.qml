import QtQuick 2.0

Item {
    id: alertLamp;
    width: 70;
    height: 100;

    property int alert: 1;
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
            source: "alert_lost.png"
            visible: alertLamp.alert==2;
        }

        Image {
            source: "alert_ok.png"
            visible: alertLamp.alert==0;
        }

        Image {
            source: "alert_disconnected.png"
            visible: alertLamp.alert==1;
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

