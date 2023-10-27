import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        id: playersScoreRect

        clip: true
        height: 64
        color: "green"

        property bool highlighted: false
        onHighlightedChanged: highlightRect.visible = highlighted

        readonly property string name: playerName.text
        readonly property string score: playerScore.text

        property string id: ""

        signal setName(string name)
        onSetName: name => playerName.text = name

        signal updateScore(int score)
        onUpdateScore: score => playerScore.text = score.toString()

        signal updateStatistic(string average, int low, int high)
        onUpdateStatistic: (average, low, high) => {
                                   averageText.text = average
                                   lowText.text = low
                                   highText.text = high
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
                columns: 3
                rowSpacing: 0
                Text {
                        id: playerName
                        Layout.columnSpan: 3
                        text: ""
                        Layout.minimumHeight: 48
                        Layout.maximumHeight: 48
                        Layout.fillWidth: true
                        font.pointSize: 18
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }
                Text {
                        id: playerScore
                        Layout.columnSpan: 3
                        text: "-1"
                        Layout.minimumHeight: 80
                        Layout.maximumHeight: 80
                        Layout.fillWidth: true
                        font.pointSize: 96
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }

                Text {
                        id: averageTitle
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        text: "Average"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: lowTitle
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        text: "Worst"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: highTitle
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        text: "Best"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: averageText
                        Layout.maximumHeight: 12
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: lowText
                        Layout.maximumHeight: 14
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: highText
                        Layout.maximumHeight: 12
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                }

                Rectangle {
                        Layout.columnSpan: 3
                        Layout.fillHeight: true
                }
        }
}
