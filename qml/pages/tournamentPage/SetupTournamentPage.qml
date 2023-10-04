import QtQuick 2.0
import QtQml.Models 2.3
import QtQuick.Layouts 1.3

import "../../components/buttons"
import "../../components/pages"
import "../../components/userInputs"
import "../../components/itemViews"

BlackPage {
        signal requestTournamentPage

        GridLayout {
                width: 768
                height: parent.height
                anchors.centerIn: parent
                rowSpacing: 24
                flow: GridLayout.TopToBottom

                Text {
                        font.pointSize: 24
                        text: "Players"
                        color: "white"
                }

                TextInputField {
                        height: 32
                        width: 512
                        Layout.alignment: Qt.AlignHCenter
                        onValueChanged: playerNamesList.appendName(value)
                }

                PlayersView {
                        id: playerNamesList
                        width: 256
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                }

                Rectangle {
                        height: 1
                        Layout.fillWidth: true
                        color: "white"
                }

                NewPushButton {
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
}
