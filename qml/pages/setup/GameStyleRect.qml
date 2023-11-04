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
                x: 5
                y: 0
                width: 96
                height: 32
                text: title
                color: "white"
                font.pointSize: 28
                font.weight: Font.Bold
        }

        Text {
                x: parent.width - width - 5
                y: 0
                anchors.top: parent.top
                height: 32
                text: optionRect.initialScore
                color: "white"
                font.pointSize: 28
                font.weight: Font.Bold
        }

        Text {
                x: 5
                y: 48
                height: parent.height - 48 - 5
                width: parent.width - 5
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
