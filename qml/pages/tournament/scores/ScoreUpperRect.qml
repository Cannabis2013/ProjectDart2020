import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        color: "transparent"

        function setName(name) {
                playerName.text = name
        }

        function showCounter(status) {
                turnCounter.visible = status
        }

        function updateCounter(count) {
                turnCounter.setNumberOfDarts(3 - count)
        }

        GridLayout {
                anchors.fill: parent
                Rectangle {
                        width: 6
                }

                Text {
                        id: playerName
                        Layout.fillHeight: true
                        font.pointSize: 18
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                }

                DartsCounter {
                        id: turnCounter
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }
        }
}
