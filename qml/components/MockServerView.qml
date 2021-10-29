import QtQuick 2.15
import QtQuick.Controls 2.15

import '../elements'

ListView {
    id: _mockView
    clip: true
    leftMargin: 20

    property var host
    property var endpoint

    delegate: RowView {
        width: _mockView.width
        height: _hostsView.height+20
        text: model.name

        property var hostsModel: model.hosts

        onClicked: {
            _mockView.model.appendHost(index, "test2.com")
        }

        ListView {
            id: _hostsView
            y: 25
            width: parent.width
            height: contentHeight

            leftMargin: 20
            model: hostsModel

            delegate: RowView {
                id: _hostDelegate
                width: parent.width
                height: _endpointsView.height+30
                text: model.hostname

                property var host: model
                property var endpoints: model.endpoints

                onClicked: {
                    _hostsView.model.appendEndpoint(index, '/path')
                }

                ListView {
                    id: _endpointsView
                    y: 30
                    width: parent.width
                    height: contentHeight
                    leftMargin: 20
                    model: endpoints
                    delegate: RowView {
                        height: 30
                        text: model.path
                        onClicked: {
                            _mockView.host = _hostDelegate.host
                            _mockView.endpoint = model
                        }
                    }
                }
            }
        }
    }
}
