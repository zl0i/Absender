import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: _row
    width: parent.width
    height: 30

    property alias text: _label.text

    signal clicked()

    Rectangle {
        width: parent.width
        height: 25
        color:_mouseArea.containsMouse ? (_mouseArea.containsPress ? "#A0C4C4C4" : "#40C4C4C4" ) : "#00000000"
        Label {
            id: _label
            x: 10
            width: parent.width
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            color: "#FFFFFF"
        }
    }

    MouseArea {
        id: _mouseArea
        width: parent.width
        height: parent.height
        hoverEnabled: true
        onClicked: _row.clicked()
    }
}
