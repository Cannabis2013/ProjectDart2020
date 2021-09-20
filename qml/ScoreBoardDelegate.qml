import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13

MyRectangle{
    id: delegateBody
    clip: true
    radius: 10
    readonly property int cellHeight: delegateBody.height
    // Point rect properties
    property int cellBorderRadius: 0
    onCellBorderRadiusChanged: delegateBody.radius = cellBorderRadius
    property bool pointDisplayVisible: false
    onPointDisplayVisibleChanged: pointTextRect.visible = pointDisplayVisible
    property int pointDisplayWidth: 20
    onPointDisplayWidthChanged: pointTextRect.width = pointDisplayWidth
    property int pointDisplayHeight: 20
    onPointDisplayHeightChanged: pointTextRect.height = pointDisplayHeight
    property color pointRectBackground: "blue"
    onPointRectBackgroundChanged: pointTextRect.color = pointRectBackground
    property color cellColor: "purple"
    onCellColorChanged: delegateBody.color = cellColor
    property color pointRectFontColor: "white"
    onPointRectFontColorChanged:  pointTextRect.color = textColor
    property int pointFontSize: 16
    onPointFontSizeChanged: pointText.font.pointSize = pointFontSize
    property string point: ""
    onPointChanged: pointText.text = point
    // Score rect properties
    property color scoreRectFontColor: "white"
    onScoreRectFontColorChanged: scoreTextRect.color = scoreRectFontColor
    property int scoreFontSize: 16
    onScoreFontSizeChanged: scoreText.font.pointSize = scoreFontSize
    property string score: ""
    onScoreChanged: scoreText.text = score
    property double cellBorderWidth: 0
    onCellBorderWidthChanged: delegateBody.border.width = cellBorderWidth
    property color cellBorderColor: "black"
    onCellBorderColorChanged: delegateBody.border.color = cellBorderColor
    property int horizontalScoreTextAlignment: Text.AlignHCenter
    onHorizontalScoreTextAlignmentChanged:  scoreText.horizontalAlignment = horizontalScoreTextAlignment
    property int verticalTextAlignment: Text.AlignVCenter
    onVerticalTextAlignmentChanged: scoreText.verticalAlignment = verticalTextAlignment
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
                radius: delegateBody.radius
            }
        }
    }
    MyRectangle{
        id: scoreTextRect
        clip: true
        anchors.fill: parent
        bottomBorderWidth: 1
        rightBorderWidth: 1
        color: "green"
        Text {
            id: scoreText
            anchors.fill: parent
            horizontalAlignment: delegateBody.horizontalScoreTextAlignment
            verticalAlignment: delegateBody.verticalTextAlignment
            color: delegateBody.scoreRectFontColor
            font.pointSize: scoreFontSize
        }
    }
    MyRectangle{
        id: pointTextRect
        x: 3
        y: 3
        width: delegateBody.pointDisplayWidth
        height:  delegateBody.pointDisplayHeight
        radius: 10
        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        clip: true
        visible: delegateBody.pointDisplayVisible
        color: delegateBody.pointRectBackground
        Text {
            id: pointText
            anchors.fill: parent
            horizontalAlignment: delegateBody.horizontalScoreTextAlignment
            verticalAlignment: delegateBody.verticalTextAlignment
            color: delegateBody.pointRectFontColor
            font.pointSize: delegateBody.pointFontSize
        }
    }
}
