import QtQuick 2.15
import QtQuick.Controls 2.15

import "./components"

Item {
    id: _page

    Label {
        z: 5
        x: 20; y: 20
        font.pixelSize: 32
        color: "#FFFFFF"
        text: qsTr("MockServers")
    }

    Rectangle {
        x: -1
        width: parent.width/5
        height: parent.height
        border { width: 1; color: "#C4C4C4" }
        color: "#1A1A1A"
        MockServerView {
            id: _mocksView
            x: 20; y: 100
            width: parent.width - x*2
            height: parent.height - y
            model: project.mocks
        }
    }

    Row {
        x: parent.width/5 + 50
        y: 100
        spacing: 10
        height: 40
        TextField {
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            text: _mocksView.endpoint ? _mocksView.endpoint.method : ''
            onEditingFinished: _mocksView.endpoint.method = text
        }
        TextField {
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 14
            text: _mocksView.endpoint ? ("http://" + _mocksView.host.hostname + _mocksView.endpoint.path) : ''
            onEditingFinished: _mocksView.endpoint.path = text
        }
    }
}
