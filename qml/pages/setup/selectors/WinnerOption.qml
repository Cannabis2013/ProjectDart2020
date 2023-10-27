import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle {
        id: optionRect

        signal clicked

        property string initialScore: ""
        property string title: ""
        property string description: ""

        radius: 12
        color: "green"

        Rectangle {
                id: innerRect
                color: "transparent"
                width: parent.width - 12
                height: parent.height - 12
                anchors.centerIn: parent
                Text {
                        id: optionTitle
                        anchors.left: parent.left
                        anchors.top: parent.top
                        width: 96
                        height: 32
                        text: title
                        color: "white"
                        font.weight: Font.Bold
                        font.pointSize: 20
                }

                Text {
                        id: initText
                        anchors.right: parent.right
                        anchors.top: parent.top
                        height: 12
                        width: 36
                        text: optionRect.initialScore
                        color: "white"
                        font.pointSize: 24
                        font.weight: Font.Bold
                }

                Text {
                        id: optionDescription
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        height: parent.height / 2
                        width: parent.width
                        text: qsTr(description)
                        wrapMode: Text.WordWrap
                        font.pointSize: 12
                        color: "white"
                }
        }

        MouseArea {
                anchors.fill: parent
                onReleased: optionRect.clicked()
        }
}
