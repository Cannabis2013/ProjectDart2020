import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        id: playersScoreRect

        clip: true
        height: 80
        color: "green"

        property bool highlighted: false
        onHighlightedChanged: highlightRect.visible = highlighted

        readonly property string name: playerName.text
        readonly property string score: playerScore.text

        signal setName(string name)
        onSetName: playerName.text = name

        signal setScore(int score)
        onSetScore: playerScore.text = score.toString()

        Rectangle {
                id: highlightRect
                color: "blue"
                opacity: 0.5
                anchors.fill: parent
                visible: false
        }

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                Text {
                        id: playerName
                        text: "Martin"
                        Layout.fillWidth: true
                        height: 48
                        font.pointSize: 40
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }
                Text {
                        id: playerScore
                        text: "-1"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        font.pointSize: 96
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }
        }
}
