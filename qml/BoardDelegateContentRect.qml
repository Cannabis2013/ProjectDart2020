import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13

BoxedRect{
    id: scoreTextRect
    clip: true
    property string playerName: ""
    onPlayerNameChanged: playerNameText.text = playerName
    property string score: ""
    onScoreChanged: scoreText.text = score
    property string averageValue: ""
    onAverageValueChanged: averageValueText.text = "Avg: " + averageValue
    property string lowerValue: ""
    onLowerValueChanged: "L: " + lowerValue
    property string upperValue: ""
    onUpperValueChanged: "H: " + upperValue
    color: "green"
    radius: 10
    bottomBorderWidth: 1
    topBorderWidth: 1
    paddingLeft: 2
    contentRect: Item{
        GridLayout{
            anchors.fill: parent
            rows: 2
            columns: 5
            Text {
                id: playerNameText
                Layout.row: 0
                Layout.column: 0
                Layout.columnSpan: 4
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 24
                text: scoreTextRect.playerName
                wrapMode: Text.WordWrap
            }
            Rectangle{
                Layout.row: 1
                Layout.column: 3
                Layout.fillWidth: true
            }

            Text {
                id: scoreText
                Layout.row: 0
                Layout.column: 4
                Layout.rowSpan: 2
                Layout.minimumWidth: 128
                Layout.maximumWidth: 128
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 32
                text: scoreTextRect.score
            }
            Text {
                id: averageValueText
                Layout.minimumWidth: 80
                Layout.maximumWidth: 80
                Layout.row: 1
                Layout.column: 0
                horizontalAlignment: Qt.AlignLeft
                color: "white"
                font.pointSize: 12
                text: "Avg: " + scoreTextRect.averageValue
            }
            Text {
                id: highestValueText
                Layout.row: 1
                Layout.column: 1
                Layout.minimumWidth: 48
                Layout.maximumWidth: 48
                horizontalAlignment: Qt.AlignLeft
                color: "white"
                font.pointSize: 12
                text: "H: " + scoreTextRect.upperValue
            }
            Text {
                id: lowestValueText
                Layout.row: 1
                Layout.column: 2
                horizontalAlignment: Qt.AlignLeft
                color: "white"
                font.pointSize: 12
                text: "L: " + scoreTextRect.lowerValue
            }
        }
    }
}
