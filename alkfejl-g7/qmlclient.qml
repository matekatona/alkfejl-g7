import QtQuick 2.0
import QtQuick.Controls 1.2

//We should use this as the base: https://github.com/csorbakristof/alkalmazasfejlesztes/blob/master/QmlControlKupac

Rectangle {
    width: 500
    height: 500

    Button {
        id: button1
        x: 55
        y: 49
        width: 126
        height: 65
        text: qsTr("Button")
    }
}

