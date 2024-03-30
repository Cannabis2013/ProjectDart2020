import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle {
        id: optionRect

        signal clicked

        property string initialScore: ""
        property string title: ""
        property string description: ""

        color: "green"

        Text {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 6
                width: 96
                height: 32
                text: title
                color: "white"
                font.pointSize: 28
                font.weight: Font.Bold
        }

        Text {
                anchors.right: parent.right
                anchors.rightMargin: 6
                anchors.top: parent.top
                height: 32
                text: optionRect.initialScore
                color: "white"
                font.pointSize: 28
                font.weight: Font.Bold
        }

        Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 6
                anchors.rightMargin: 6
                anchors.top: parent.verticalCenter
                text: qsTr(description)
                wrapMode: Text.WordWrap
                font.pointSize: 18
                color: "white"
        }

        MouseArea {
                anchors.fill: parent
                onReleased: optionRect.clicked()
        }
}
