import QtQuick 2.15
import QtQuick.Controls 2.15

import "../elements"

Dialog {
    id: _dialog
    parent: Overlay.overlay
    x: parent.width/2 - width/2
    y: parent.height/2 - height/2
    width: 450
    height: 150
    padding: 0

    signal create(string name)

    background: Rectangle {
        color: "#292929"
        radius: 10
        border { width: 1; color: "#80C4C4C4" }
    }

    contentItem: Item {
        TextField {
            id: _fieldName
            x: 25; y: 25
            width: parent.width - 50
            height: 40
            color: "#FFFFFF"
            placeholderTextColor: "#FFFFFF"
            placeholderText: qsTr("Porject name")
            background: Rectangle {
                color: "#00000000"
                border { width: 1; color: "#80C4C4C4" }
            }
        }

        AButton {
            x: parent.width - width - 25
            y: parent.height - height - 25
            text: qsTr("Create")
            onClicked: _dialog.create(_fieldName.text)
        }
    }
}
