import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls

import "../../templates"
import "./playersView"
import "../../../sharedComponents/userInputs"
import "../../../sharedComponents/buttons"
import "../selectors"
import "setupScripts.js" as Setup

PageWithHeader {
        id: setupPage

        signal requestTournamentPage

        buttonText: "Menu"
        pageTitle: "Setup tournament"

        GridLayout {
                width: 768
                anchors.fill: parent
                rowSpacing: 24
                flow: GridLayout.TopToBottom

                Text {
                        font.pointSize: 24
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                        text: "Game style"
                        color: "white"
                }

                WinnerSelector {
                        id: winnerSelector
                        width: 256
                        height: 128
                        Layout.alignment: Qt.AlignHCenter
                }

                Text {
                        font.pointSize: 24
                        Layout.fillWidth: true
                        text: "Players"
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                }

                TextInputField {
                        height: 32
                        width: 256
                        placeholder: "Add player name"
                        Layout.alignment: Qt.AlignHCenter
                        onValueChanged: value => playerNamesList.appendName(value)
                }

                PlayersView {
                        id: playerNamesList
                        width: 256
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                }

                ButtonGroup {
                        height: 48
                        width: 256
                        Layout.alignment: Qt.AlignHCenter
                        acceptButtonTitle: "Play"
                        onBackClicked: setupPage.backClicked()
                        onAcceptClicked: Setup.startGame()
                }
        }
}
