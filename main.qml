import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15


import './qml'

ApplicationWindow {
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Absender")

    background: Rectangle {
        color: "#1A1A1A"
    }


    StackView {
        id: _stackView
        x: 70
        width: parent.width - 70
        height: parent.height
        initialItem: _dashboard
    }

    Dasboard {
        id: _dashboard
        visible: false
        projects: recents
    }
    API {
        id: _api
        visible: false
    }
    MockServers {
        id: _mockServers
        visible: false
    }

    Rectangle {
        width: 70
        height: parent.height
        color: "#1A1A1A"
        border { width: 1; color: "#C4C4C4" }

        Column {
            x:1; y: 1
            width: parent.width-2
            Repeater {
                model: ['Projects', 'API', 'Mock Servers']
                delegate:   Rectangle {
                    x:1; y: 1
                    width: parent.width-2
                    height: width
                    color: _mouseArea.containsMouse ? (_mouseArea.containsPress ? "#A0C4C4C4" : "#40C4C4C4" ) : "#00000000"
                    Label {
                        width: parent.width
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: "#FFFFFF"
                        text: modelData
                    }


                    MouseArea {
                        id: _mouseArea
                        width: parent.width
                        height: parent.height
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            switch (modelData) {
                            case "Projects":
                                _stackView.replace(_dashboard)
                                break
                            case "API":
                                _stackView.replace(_api)
                                break
                            case "Mock Servers":
                                _stackView.replace(_mockServers)
                                break
                            }
                        }
                    }
                }
            }
        }
    }
}
