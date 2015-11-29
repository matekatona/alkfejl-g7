import QtQuick 2.4

Item {
    id: gyroIndicator;
    width: 200;
    height: 230;

    property int angle: 0;
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
        x:77; y:80;
        source: "top.png";
        visible: gyroIndicator.view=="top";
        smooth: true;
        transform: Rotation {
            id: topRotation
            origin.x: 23;
            origin.y: 50;
            angle: gyroIndicator.angle;
        }
    }

    Image{
        id:front;
        x:65; y:104;
        source: "front.png";
        visible: gyroIndicator.view=="front";
        smooth: true;
        transform: Rotation {
            id: frontRotation
            origin.x: 35;
            origin.y: 26;
            angle: gyroIndicator.angle;
        }
    }

    Image{
        id:right;
        x:50; y:112;
        source: "right.png";
        visible: gyroIndicator.view=="right";
        smooth: true;
        transform: Rotation {
            id: rightRotation
            origin.x: 50;
            origin.y: 18;
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
