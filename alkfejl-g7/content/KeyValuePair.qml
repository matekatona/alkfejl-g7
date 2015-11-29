import QtQuick 2.0

Item {
    id: keyValuePair;
    width: 220;

    property alias key: key.text;
    property alias value: value.text;

    function setValue(value){
        keyValuePair.value=value;
    }

    Text{
        id: key;
        width: 130;
    }
    Text{
        id: value;
        width: 90;
        anchors.left: key.right;
        horizontalAlignment: Text.AlignRight;
        color: "gray";
    }
}

