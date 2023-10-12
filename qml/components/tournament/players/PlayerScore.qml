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

        property string id: ""

        signal setName(string name)
        onSetName: playerName.text = name

        signal updateScore(int score)
        onUpdateScore: playerScore.text = score.toString()

        signal updateStatistic(string average, int low, int high)
        onUpdateStatistic: {
                averageText.text = "Average: " + average
                lowText.text = "Worst: " + low
                highText.text = "Best: " + high
        }

        property double average: 0.0

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
                        text: ""
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

                GridLayout {
                        Layout.fillWidth: true
                        Layout.minimumHeight: 16
                        Layout.maximumHeight: 16
                        Rectangle {
                                width: 3
                        }

                        Text {
                                id: averageText
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                font.pointSize: 10
                                color: "white"
                                text: "Average: 0"
                        }

                        Text {
                                id: lowText
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                font.pointSize: 10
                                color: "white"
                                text: "Worst: 0"
                        }

                        Text {
                                id: highText
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                font.pointSize: 10
                                color: "white"
                                text: "Best: 0"
                        }

                        Rectangle {
                                width: 3
                        }
                }
        }
}
