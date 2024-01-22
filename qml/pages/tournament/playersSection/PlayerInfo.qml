import QtQuick 2.15
import QtQuick.Layouts 1.3
import "playerInfo.js" as Scripts

Rectangle {
        id: infoRect

        color: "green"

        Behavior on color {
                ColorAnimation {
                        duration: 300
                }
        }

        readonly property string name: playerName.text

        function setPlayerName(name) {
                playerName.text = name
        }

        function highlight(status, count) {
                Scripts.highlight(status, count)
        }

        GridLayout {
                anchors.fill: parent
                columnSpacing: 0

                Text {
                        id: playerName
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 20
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                }

                DartsCounter {
                        id: dartsCounter
                        Layout.preferredHeight: 32
                        Layout.preferredWidth: 44
                        Layout.alignment: Qt.AlignVCenter
                }
        }
}
