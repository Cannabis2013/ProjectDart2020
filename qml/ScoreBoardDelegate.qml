import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13

MyRectangle{
    id: delegateBody
    clip: true
    readonly property int cellHeight: delegateBody.height
    // Point rect properties
    property int cellBorderRadius: 0
    onCellBorderRadiusChanged: delegateBody.radius = cellBorderRadius
    property color cellColor: "purple"
    onCellColorChanged: delegateBody.color = cellColor
    property string point: ""
    onPointChanged: pointText.text = point
    // Score rect properties
    property string score: ""
    onScoreChanged: scoreTextRect.text = score
    property double cellBorderWidth: 0
    onCellBorderWidthChanged: delegateBody.border.width = cellBorderWidth
    property color cellBorderColor: "black"
    onCellBorderColorChanged: delegateBody.border.color = cellBorderColor
    bottomBorderWidth: 1
    rightBorderWidth: 1
    implicitWidth: 25
    implicitHeight: 25
    property string g: ""
    color: cellColor
    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: delegateBody.width
            height: delegateBody.height
            Rectangle{
                anchors.fill: parent
                radius: delegateBody.radius
            }
        }
    }
    BoardDelegateContentRect {
        id: scoreTextRect
    }
}
