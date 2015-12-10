import QtQuick 2.0

Item {
    id: textHistory;

    anchors.left: parent.left;

    anchors.horizontalCenter: parent.horizontalCenter;

    anchors.margins: 30;

    width: 140;
    height: 300;

    property var history: ["UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN"];

    function addValue(value)
    {
        var newHistory=new Array(10);
        newHistory[0]=value;
        for(var i=0;i<9;i++)
            newHistory[i+1]=history[i];
        history=newHistory;
    }

    Item {
        id: values;

        Repeater {
            model: 10;

            Text {
                y: index*30;
                text: textHistory.history[index];
            }
        }
    }
}

