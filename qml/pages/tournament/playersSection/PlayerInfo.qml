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

        function setPlayer(name, nationality) {
                Scripts.setPlayer(name, nationality)
        }

        function highlight(status, count) {
                Scripts.highlight(status, count)
        }

        GridLayout {
                anchors.centerIn: parent
                width: parent.width - 12
                height: parent.height
                columnSpacing: 0
                columns: 2

                Text {
                        id: playerName
                        Layout.columnSpan: 2
                        Layout.fillHeight: true
                        Layout.fillWidth: true
<<<<<<< Updated upstream
                        font.pointSize: 24
=======
                        font.pointSize: 22
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                }

                Text {
                        id: playerNationality
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 16
>>>>>>> Stashed changes
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                }

                DartsCounter {
                        id: dartsCounter
                        Layout.preferredHeight: 32
                        Layout.preferredWidth: 44
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                }
        }
}
