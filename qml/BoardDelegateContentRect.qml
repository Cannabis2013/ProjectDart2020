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
    onScoreChanged: scoreText.text = text
    color: "green"
    bottomBorderWidth: 1
    topBorderWidth: 1
    anchors.fill: parent
    paddingLeft: 2
    contentRect: Item{
        GridLayout{
            anchors.fill: parent
            rows: 1
            columns: 2
            Text {
                id: playerNameText
                Layout.fillWidth: true
                Layout.row: 0
                Layout.column: 0
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 20
                text: scoreTextRect.playerName
                wrapMode: Text.WordWrap
            }
            Text {
                id: scoreText
                Layout.minimumWidth: 80
                Layout.maximumWidth: 80
                Layout.row: 0
                Layout.column: 1
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 28
                text: scoreTextRect.text
            }
        }
    }
}
