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

        Text {
                id: optionTitle
                x: 5
                y: 5
                width: 96
                height: 32
                text: title
                color: "white"
                font.weight: Font.Bold
                font.pointSize: 28
        }

        Text {
                id: initText
                x: parent.width - width - 5
                y: 5
                anchors.top: parent.top
                height: 12
                text: optionRect.initialScore
                color: "white"
                font.pointSize: 24
                font.weight: Font.Bold
        }

        Text {
                id: optionDescription
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
