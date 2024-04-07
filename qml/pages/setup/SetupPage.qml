import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../templates"
import "setupPage.js" as Scripts

PageWithHeader {
        anchors.fill: parent
        pageTitle: "Gamestyles"

        signal requestTournamentPage

        ModesModel {
                id: dataModel
        }

        Component {
                id: delegate
                GameStyleRect {
                        onClicked: index => Scripts.initFromIndex(index)
                }
        }

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                Text {
                        Layout.preferredHeight: 32
                        Layout.fillWidth: true
                        font.pointSize: 24
                        color: "white"
                        text: "Choose a game style"
                        horizontalAlignment: Text.AlignHCenter
                }

                ListView {
                        clip: true
                        cacheBuffer: 6
                        spacing: 6
                        maximumFlickVelocity: 300
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        model: dataModel
                        delegate: delegate
                }
        }
}
