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
    onAverageValueChanged: statsView.averageValue = averageValue
    property string lowerValue: ""
    onLowerValueChanged: statsView.lowerValue = lowerValue
    property string upperValue: ""
    onUpperValueChanged: statsView.upperValue = upperValue
    color: "green"
    radius: 10
    bottomBorderWidth: 1
    topBorderWidth: 1
    paddingLeft: 2
    contentRect: Item{
        GridLayout{
            anchors.fill: parent
            rows: 2
            columns: 2
            Text {
                id: playerNameText
                Layout.row: 0
                Layout.column: 0
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignBottom
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "white"
                font.pointSize: 20
                text: scoreTextRect.playerName
                wrapMode: Text.WordWrap
            }
            Text {
                id: scoreText
                Layout.row: 0
                Layout.column: 1
                Layout.rowSpan: 2
                Layout.minimumWidth: 96
                Layout.maximumWidth: 96
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 32
                text: scoreTextRect.score
            }
            DartsStatsView{
                id: statsView
                Layout.row: 1
                Layout.column: 0
                Layout.fillWidth: true
            }
        }
    }
}
