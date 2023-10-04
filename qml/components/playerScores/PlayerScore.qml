import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        clip: true
        width: 128
        height: 80
        color: "transparent"

        readonly property string name: playerName.text
        readonly property string score: playerScore.text

        signal setName(string name)
        onSetName: playerName.text = name

        signal setScore(int score)
        onSetScore: playerScore.text = score.toString()

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                Text {
                        id: playerName
                        text: "Martin"
                        Layout.fillWidth: true
                        height: 48
                        font.pointSize: 12
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }
                Text {
                        id: playerScore
                        text: "501"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        font.pointSize: 28
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }
        }
}
