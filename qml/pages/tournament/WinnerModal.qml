import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

import "./turn"
import "./players"
import "./keyPad"
import "../templates"
import "tournamentPageScripts.js" as PageScripts

Rectangle {
        id: winnerModal
        color: "transparent"
        radius: 12
        anchors.fill: parent

        signal restartClicked

        Rectangle {
                anchors.fill: parent
                color: "black"
                opacity: 0.5
        }

        MouseArea {
                anchors.fill: parent
        }

        function show(text) {
                winnerModal.visible = true
                winnerText.text = text
        }

        Rectangle {
                color: "grey"
                anchors.centerIn: parent
                width: 256
                height: 256
                radius: 12

                MouseArea {
                        anchors.fill: parent
                }

                GridLayout {
                        anchors.fill: parent
                        flow: GridLayout.TopToBottom
                        Text {
                                id: winnerText
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                font.pointSize: 32
                                font.weight: Font.Bold
                                verticalAlignment: Qt.AlignVCenter
                                horizontalAlignment: Qt.AlignHCenter
                        }
                        Button {
                                Layout.alignment: Qt.AlignHCenter
                                width: 128
                                height: 32
                                text: "Restart"
                                onClicked: {
                                        winnerModal.visible = false
                                        restartClicked()
                                }
                        }
                }
        }
}
