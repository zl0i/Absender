import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

import "./components"
import "./elements"

Item {
    id: _page

    property var projects    

    Row {
        x: 20; y: 20
        spacing: 15

        Label {
            color: "#FFFFFF"
            text: qsTr("Проекты")
        }
        AButton {
            text: qsTr("Новый")
            onClicked: _newProjectDialog.open()
        }
        AButton {
            text: qsTr("Открыть")
            onClicked: _fileDialog.open()
        }
    }


    Flickable {
        x: 40; y: 70
        width: parent.width - 80
        height: parent.height - 100
        contentHeight: _projectsFlow.height
        clip: true
        Flow {
            id: _projectsFlow
            anchors.fill: parent
            spacing: 30
            Repeater {
                model: _page.projects
                delegate: Rectangle {
                    width: 200
                    height: 200
                    radius: 10
                    color: "#292929"
                    border { width: 3; color: _mouseArea.containsMouse ? "blue" : "#1A1A1A" }
                    Label {
                        x: 20; y: 20
                        font.pixelSize: 16
                        color: "#FFFFFF"
                        text: model.name
                    }

                    MouseArea {
                        id: _mouseArea
                        width: parent.width
                        height: parent.height
                        hoverEnabled: true
                        onClicked: gui.openProject(model.path)
                    }
                }
            }
        }
    }

    NewProjectDialog {
        id: _newProjectDialog
        onCreate: {
            gui.createNewProject(name, "")
            close()
        }
    }

    FileDialog {
        id: _fileDialog
        nameFilters: [ "Absender files (*.abs *.json)", "All files (*)" ]
        onAccepted: gui.openProject(fileUrl)
    }
}
