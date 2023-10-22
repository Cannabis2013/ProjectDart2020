import QtQuick 2.15
import QtQuick.Controls

Rectangle {
        id: viewDelegate
        width: 256
        height: 64
        clip: true
        radius: 12
        color: "grey"
        Text {
                anchors.fill: parent
                text: name
                font.pointSize: 20
                color: "white"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
        }
        Button {
                x: 231
                y: 5
                width: 20
                height: 20
                background: Rectangle {
                        color: "red"
                        anchors.fill: parent
                        radius: 24
                }

                Text {
                        anchors.fill: parent
                        text: "X"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 12
                        font.weight: Font.Bold
                        color: "white"
                }

                onClicked: playersModel.remove(index)
        }
}
