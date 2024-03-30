import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../templates"
import "setupPage.js" as Scripts

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

                Component {
                        id: gameStyleDelegate
                        GameStyleRect {
                                width: parent.width
                                height: 128
                                title: modeTitle
                                color: modeColor
                                initialScore: score
                                description: modeDescription
                                onClicked: () => Scripts.init(mode, Number.parseInt(score))
                        }
                }

                ListView {
                        id: listView
                        clip: true
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillHeight: true
                        width: 300
                        spacing: 6
                        model: GameStyles {}
                        delegate: gameStyleDelegate
                }
        }
}
