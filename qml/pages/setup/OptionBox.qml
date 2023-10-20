import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../../components/buttons"
import "../templates"

Rectangle {
        id: optionRect
        property string title: ""
        property string description: ""
        property int value: -1
        property bool selected: false
        onSelectedChanged: backDrop.color = selected ? "blue" : "green"

        radius: 12

        layer.effect: ShaderEffect {}

        Rectangle {
                id: backDrop
                radius: 12
                anchors.fill: parent
                opacity: 0.8
                color: "green"
        }

        Rectangle {
                id: innerRect
                color: "transparent"
                width: parent.width - 12
                height: parent.height - 12
                anchors.centerIn: parent
                GridLayout {
                        flow: GridLayout.TopToBottom
                        anchors.fill: parent
                        Text {
                                id: optionTitle
                                height: 32
                                Layout.fillWidth: true
                                text: qsTr(title)
                                color: "white"
                        }

                        Text {
                                id: optionDescription
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: qsTr(description)
                                wrapMode: Text.WordWrap
                                color: "white"
                        }
                }
        }

        MouseArea {
                anchors.fill: parent
                onReleased: optionClicked(optionRect.title, optionRect.value)
        }
}
