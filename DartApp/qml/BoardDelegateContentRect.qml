import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13
BoxedRect{
    id: delegateBody
    signal enableItem(bool enable)
    onEnableItem: itemEnabled = enable
    property bool itemEnabled: false
    onItemEnabledChanged: opacity = itemEnabled ?  1 : 0.7
    opacity: 0.7
    property string playerName: ""
    onPlayerNameChanged: playerNameText.text = playerName
    property string score: ""
    onScoreChanged: scoreText.text = score
    property string midValue: ""
    onMidValueChanged: statsView.midValue = midValue
    property string minValue: ""
    onMinValueChanged: statsView.minValue = minValue
    property string maxValue: ""
    onMaxValueChanged: statsView.maxValue = maxValue
    color: "green"
    radius: 10
    bottomBorderWidth: 1
    padding: 2
    contentRect: GridLayout{
        rows: 2
        columns: 2
        TextRect {
            id: playerNameText
            Layout.row: 0
            Layout.column: 0
            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignBottom
            Layout.fillWidth: true
            Layout.fillHeight: true
            fontColor: "white"
            fontSize: 20
            text: delegateBody.playerName
            wrapMode: Text.WordWrap
        }
        TextRect {
            id: scoreText
            Layout.row: 0
            Layout.column: 1
            Layout.rowSpan: 2
            Layout.minimumWidth: 96
            Layout.maximumWidth: 96
            Layout.fillHeight: true
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            fontColor: "white"
            fontSize: 26
            text: delegateBody.score
        }
        DartsStatsView{
            id: statsView
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.minimumHeight: 14
            Layout.maximumHeight: 14
            fontSize: 10
        }
    }
}
