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

                Flickable {
                        id: flickable
                        clip: true
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillHeight: true
                        maximumFlickVelocity: 1000
                        width: 300
                        contentWidth: 300
                        Column {
                                id: flickableContent
                                width: parent.width
                                spacing: 6
                        }

                        Component.onCompleted: Scripts.initFlickable()
                }
        }
}
