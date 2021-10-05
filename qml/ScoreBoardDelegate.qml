import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13
MyRectangle{
    id: delegateBody
    clip: true
    readonly property int cellHeight: delegateBody.height
    // Score rect properties
    property string playerName: ""
    onPlayerNameChanged: scoreTextRect.playerName = playerName
    property string score: ""
    onScoreChanged: scoreTextRect.text = score
    property color cellBorderColor: "black"
    onCellBorderColorChanged: delegateBody.border.color = cellBorderColor
    bottomBorderWidth: 1
    rightBorderWidth: 1
    implicitWidth: 25
    implicitHeight: 25
    property string text: ""
    color: cellColor
    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: delegateBody.width
            height: delegateBody.height
            Rectangle{
                anchors.fill: parent
                radius: 10
            }
        }
    }
    BoardDelegateContentRect {
        id: scoreTextRect
        anchors.fill: parent
    }
}
