import QtQuick 2.15
import QtQuick.Controls 2.15

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
        ListView {
            id: _mockView
            x: 20; y: 100
            width: parent.width - x*2
            height: parent.height - y
            clip: true
            leftMargin: 20
            model: project.mocks

            delegate: Item {
                id: _server
                width: _mockView.width
                height: _hostsView.height+20

                property var hostsModel: model.hosts

                Label {
                    width: parent.width
                    height: parent.height
                    color: "#FFFFFF"
                    text: model.name
                }
                ListView {
                    id: _hostsView
                    y: 25
                    width: parent.width
                    height: contentHeight
                    leftMargin: 20
                    model: _server.hostsModel


                    delegate: Item {
                        id: _hostDelegate
                        width: parent.width
                        height: _endpointsView.height+30

                        property var endpoints: model.endpoints

                        Label {
                            width: 25
                            height: 30
                            color: "#FFFFFF"
                            text: model.hostname
                        }
                        ListView {
                            id: _endpointsView
                            y: 30
                            width: parent.width
                            height: contentHeight
                            leftMargin: 20
                            model: endpoints
                            delegate: Label {
                                width: parent.width
                                height: 30
                                color: "#FFFFFF"
                                text: model.path
                            }
                        }
                    }
                }
            }
        }
    }
}
