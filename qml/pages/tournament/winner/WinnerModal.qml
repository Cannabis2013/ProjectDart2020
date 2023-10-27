import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

import "../turn"
import "../players"
import "../keyPad"

Rectangle {
        id: winnerModal
        anchors.fill: parent

        color: "black"

        signal restartClicked
        signal undoClicked

        MouseArea {
                anchors.fill: parent
        }

        function show(text) {
                winnerModal.visible = true
                winnerText.text = text
        }

        MouseArea {
                anchors.fill: parent
        }

        AnimatedImage {
                anchors.fill: parent
                source: "qrc:/pictures/Ressources/winner.gif"
        }

        GridLayout {
                anchors.fill: parent
                columns: 3

                Text {
                        id: titleText
                        Layout.columnSpan: 3
                        height: 32
                        Layout.fillWidth: true
                        text: "Winner"
                        font.pointSize: 48
                        font.weight: Font.Bold
                        horizontalAlignment: Qt.AlignHCenter
                        color: "white"
                }

                Text {
                        id: winnerText
                        Layout.columnSpan: 3
                        height: 24
                        Layout.fillWidth: true
                        font.pointSize: 32
                        font.weight: Font.Medium
                        horizontalAlignment: Qt.AlignHCenter
                        color: "white"
                }

                Rectangle {
                        Layout.fillHeight: true
                        Layout.columnSpan: 3
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.maximumWidth: 128
                        Layout.minimumHeight: 48
                        Layout.maximumHeight: 48
                        text: "Menu"
                        onClicked: {
                                winnerModal.visible = false
                                menuRequest()
                        }
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.maximumWidth: 128
                        Layout.minimumHeight: 48
                        Layout.maximumHeight: 48
                        text: "Undo"
                        onClicked: {
                                winnerModal.visible = false
                                undoClicked()
                        }
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.maximumWidth: 128
                        Layout.minimumHeight: 48
                        Layout.maximumHeight: 48
                        text: "Restart"
                        onClicked: {
                                winnerModal.visible = false
                                restartClicked()
                        }
                }
        }
}
