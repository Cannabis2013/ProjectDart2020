import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../templates"

PageWithHeader {
        anchors.fill: parent
        pageTitle: "Gamestyles"

        signal requestTournamentPage

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                Text {
                        height: 32
                        Layout.fillWidth: true
                        font.pointSize: 24
                        color: "white"
                        text: "Choose a game style"
                        horizontalAlignment: Text.AlignHCenter
                }

                GameStyles {
                        id: winnerSelector
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillHeight: true
                        width: 300
                        onOptionClicked: (mode, initialValue) => {
                                                 dartsController.init(["Druk Bruno", "Bingo Leif"], mode, initialValue)
                                                 requestTournamentPage()
                                         }
                }
        }
}
