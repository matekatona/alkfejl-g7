import QtQuick 2.4

Item {
    id: gyroIndicator;
    width: 100;
    height: 130;

    property real angle: 0;
    property alias title: titleLabel.text;
    property string view: "top";

    function setAngle(angle){
        gyroIndicator.angle=angle;
    }

    function addAngle(angle){
        gyroIndicator.angle=gyroIndicator.angle+angle;
    }

    function setView(view){
        if(view == "front")
            gyroIndicator.view="front";
        else if(view == "right")
            gyroIndicator.view="right";
        else
            gyroIndicator.view="top";
    }

    function setTitle(title){
        gyroIndicator.title=title;
    }

    Image{
        id:background;
        y:30;
        source: "background.png";
        visible: true;
    }

    Image{
        id:top;
        x:38.5; y:55;
        source: "top.png";
        visible: gyroIndicator.view=="top";
        smooth: true;
        transform: Rotation {
            id: topRotation
            origin.x: 11.5;
            origin.y: 25;
            angle: gyroIndicator.angle;
        }
    }

    Image{
        id:front;
        x:32; y:67;
        source: "front.png";
        visible: gyroIndicator.view=="front";
        smooth: true;
        transform: Rotation {
            id: frontRotation
            origin.x: 18;
            origin.y: 13;
            angle: gyroIndicator.angle;
        }
    }

    Image{
        id:right;
        x:25; y:71.5;
        source: "right.png";
        visible: gyroIndicator.view=="right";
        smooth: true;
        transform: Rotation {
            id: rightRotation
            origin.x: 25;
            origin.y: 8.5;
            angle: gyroIndicator.angle;
        }
    }

    Text{
        id:titleLabel;
        y:10;
        anchors.horizontalCenter: gyroIndicator.horizontalCenter;
        color:"black";
        font.pixelSize: 14;
        style: Text.Raised;
        styleColor: "black";
    }


}
