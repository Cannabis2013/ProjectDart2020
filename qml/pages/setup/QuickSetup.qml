import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../../components/buttons"
import "../templates"

BlackPageWithHeader {
        id: confirmPage

        anchors.fill: parent

        signal requestTournamentPage

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                EndgameSelector {
                        id: winnerSelector
                        Layout.alignment: Qt.AlignHCenter
                        height: 48
                        width: 300
                }

                Rectangle {
                        color: "transparent"
                        height: 64
                        Layout.alignment: Qt.AlignHCenter
                        width: 300
                        GridLayout {
                                anchors.fill: parent
                                PushButton {
                                        Layout.fillHeight: true
                                        width: 128
                                        text: "Back"
                                        onClicked: backClicked()
                                }

                                PushButton {
                                        Layout.fillHeight: true
                                        width: 128
                                        text: "Start"
                                        onClicked: {
                                                const mode = winnerSelector.selectedValue
                                                dartsController.init(["I", "II"], mode)
                                                requestTournamentPage()
                                        }
                                }
                        }
                }

                Rectangle {
                        height: 16
                }
        }
}
