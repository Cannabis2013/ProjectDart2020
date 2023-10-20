import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../../components/buttons"
import "../templates"
import "qmlDialogs.js" as Dialogs

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
                        onRequestDialog: Dialogs.winnerModeDialog(confirmPage, winnerSelector.setCurrentValues)
                }

                Rectangle {
                        Layout.fillHeight: true
                }

                Rectangle {
                        color: "transparent"
                        height: 24
                        Layout.alignment: Qt.AlignHCenter
                        width: 300
                        GridLayout {
                                anchors.fill: parent
                                PushButton {
                                        Layout.alignment: Qt.AlignRight
                                        Layout.fillHeight: true
                                        width: 64
                                        text: "Back"
                                        onClicked: backClicked()
                                }

                                PushButton {
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
