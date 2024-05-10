import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 6.0

Rectangle {
        id: delegateRect

        height: 128
        width: parent.width

        color: "green"

        signal clicked(int index)

        Text {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 6
                width: 96
                height: 32
                text: modeTitle
                color: "white"
                font.pointSize: 28
                font.weight: Font.Bold
        }

        Text {
                anchors.right: parent.right
                anchors.rightMargin: 6
                anchors.top: parent.top
                height: 32
                text: score
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
                text: modeDescription
                wrapMode: Text.WordWrap
                font.pointSize: 18
                color: "white"
        }

        MouseArea {
                anchors.fill: parent
                onClicked: delegateRect.clicked(index)
        }
}
