import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Absender")


    Rectangle {
        width: 70
        height: parent.height
        color: "#1A1A1A"

        Rectangle {
            width: parent.width
            height: width
            color: parent.color
            Label {
                width: parent.width
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "#FFFFFF"
                text: qsTr("Mock Servers")
            }

            MouseArea {
                width: parent.width
                height: parent.height
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    console.log('mock')
                }
            }
        }
    }
}
