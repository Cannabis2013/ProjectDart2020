import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13

MyRectangle{
    id: pointDelegateBody
    clip: true
    radius: 10
    readonly property int cellHeight: pointDelegateBody.height
    // Point rect properties
    property bool pointDisplayVisible: false
    onPointDisplayVisibleChanged: pointTextRect.visible = pointDisplayVisible
    property int pointDisplayWidth: 20
    onPointDisplayWidthChanged: pointTextRect.width = pointDisplayWidth
    property int pointDisplayHeight: 20
    onPointDisplayHeightChanged: pointTextRect.height = pointDisplayHeight
    property color pointRectBackground: "blue"
    onPointRectBackgroundChanged: pointTextRect.color = pointRectBackground
    property color cellColor: "purple"
    onCellColorChanged: pointDelegateBody.color = cellColor
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
    onCellBorderWidthChanged: pointDelegateBody.border.width = cellBorderWidth

    property color cellBorderColor: "black"
    onCellBorderColorChanged: pointDelegateBody.border.color = cellBorderColor

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
            width: pointDelegateBody.width
            height: pointDelegateBody.height
            Rectangle{
                anchors.fill: parent
                radius: pointDelegateBody.radius
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
            horizontalAlignment: pointDelegateBody.horizontalScoreTextAlignment
            verticalAlignment: pointDelegateBody.verticalTextAlignment
            color: pointDelegateBody.scoreRectFontColor
            font.pointSize: scoreFontSize
        }
    }
    MyRectangle{
        id: pointTextRect
        x: 3
        y: 3
        width: pointDelegateBody.pointDisplayWidth
        height:  pointDelegateBody.pointDisplayHeight
        radius: 10
        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        clip: true
        visible: pointDelegateBody.pointDisplayVisible
        color: pointDelegateBody.pointRectBackground
        Text {
            id: pointText
            anchors.fill: parent
            horizontalAlignment: pointDelegateBody.horizontalScoreTextAlignment
            verticalAlignment: pointDelegateBody.verticalTextAlignment
            color: pointDelegateBody.pointRectFontColor
            font.pointSize: pointDelegateBody.pointFontSize
        }
    }
}
