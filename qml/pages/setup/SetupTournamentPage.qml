import QtQuick 2.0
import QtQml.Models 2.3
import QtQuick.Layouts 1.3

import "../../components/buttons"
import "../templates"
import "../../components/playersView"
import "../../components/userInputs"

BlackPageWithHeader {
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
                        text: "Players"
                        color: "white"
                }

                TextInputField {
                        height: 32
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                        onValueChanged: playerNamesList.appendName(value)
                }

                PlayersView {
                        id: playerNamesList
                        width: 256
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                }

                EndgameSelector {
                        id: winnerSelector
                        width: 256
                        height: 48
                        onRequestDialog: optionDialog.open()
                }

                PushButton {
                        text: "Begin"
                        radius: 12
                        height: 64
                        width: 128
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                        onClicked: {
                                const names = playerNamesList.playerNames
                                if (names.length > 0) {
                                        dartsController.init(names)
                                        requestTournamentPage()
                                }
                        }
                }

                Rectangle {
                        height: 8
                }
        }

        OptionsDialog {
                id: optionDialog
                onOptionClicked: (title, value) => winnerSelector.setCurrentValues(title, value)
        }
}
