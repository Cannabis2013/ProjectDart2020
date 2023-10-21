import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../templates"

PageWithHeader {
        id: quickSetup

        anchors.fill: parent

        pageTitle: "Quick setup"

        signal requestTournamentPage

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                Text {
                        height: 32
                        Layout.fillWidth: true
                        font.pointSize: 20
                        color: "white"
                        text: "Game style"
                        horizontalAlignment: Text.AlignHCenter
                }

                WinnerSelector {
                        id: winnerSelector
                        Layout.alignment: Qt.AlignHCenter
                        height: 128
                        width: 300
                }

                Rectangle {
                        Layout.fillHeight: true
                }

                Rectangle {
                        color: "transparent"
                        height: 32
                        Layout.alignment: Qt.AlignHCenter
                        width: 300
                        GridLayout {
                                anchors.fill: parent
                                Button {
                                        Layout.alignment: Qt.AlignRight
                                        Layout.fillHeight: true
                                        width: 64
                                        text: "Back"
                                        onClicked: backClicked()
                                }

                                Button {
                                        Layout.alignment: Qt.AlignLeft
                                        Layout.fillHeight: true
                                        width: 64
                                        text: "Start"
                                        onClicked: {
                                                const mode = winnerSelector.selectedValue
                                                dartsController.init(["I", "II"], mode)
                                                requestTournamentPage()
                                        }
                                }
                        }
                }
        }
}
