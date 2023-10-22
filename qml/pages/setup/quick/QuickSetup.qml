import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../../templates"
import "../../../sharedComponents/buttons"
import "../selectors"

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
                        configKey: "quickWinCond"
                }

                Rectangle {
                        Layout.fillHeight: true
                }

                ButtonGroup {
                        height: 48
                        width: 300
                        Layout.alignment: Qt.AlignHCenter

                        acceptButtonTitle: "Play"

                        onBackClicked: quickSetup.backClicked()
                        onAcceptClicked: {
                                const mode = winnerSelector.selectedValue
                                dartsController.init(["I", "II"], mode)
                                requestTournamentPage()
                        }
                }
        }
}
