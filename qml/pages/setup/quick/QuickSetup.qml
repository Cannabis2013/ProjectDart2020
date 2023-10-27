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
                        Layout.fillHeight: true
                        width: 300
                        onOptionClicked: (mode, initialValue) => {
                                                 dartsController.init(["I", "II"], mode, initialValue)
                                                 requestTournamentPage()
                                         }
                }
        }
}
