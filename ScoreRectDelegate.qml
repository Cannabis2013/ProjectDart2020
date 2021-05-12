import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13

MyRectangle{
    id: cellBody
    clip: true

    readonly property int cellHeight: cellBody.height

    property int cellBorderRadius: 0
    onCellBorderRadiusChanged: maskedRect.radius = cellBorderRadius

    property color cellColor: "purple"
    onCellColorChanged: cellBody.color = cellColor

    property color textColor: "white"
    onTextColorChanged: scoreText = textColor

    property int pointFontSize: 16
    onPointFontSizeChanged: pointText.font.pointSize = pointFontSize

    property int scoreFontSize: 16
    onScoreFontSizeChanged: scoreText.font.pointSize = scoreFontSize

    property double cellBorderWidth: 0
    onCellBorderWidthChanged: cellBody.border.width = cellBorderWidth

    property color cellBorderColor: "black"
    onCellBorderColorChanged: cellBody.border.color = cellBorderColor

    property int horizontalTextAlignment: Text.AlignHCenter
    onHorizontalTextAlignmentChanged: scoreText.horizontalAlignment = horizontalTextAlignment

    property int verticalTextAlignment: Text.AlignVCenter
    onVerticalTextAlignmentChanged: scoreText.verticalAlignment = verticalTextAlignment

    bottomBorderWidth: 1
    rightBorderWidth: 1

    implicitWidth: 25
    implicitHeight: 25

    property string point: ""
    onPointChanged: pointText.text = point
    property string score: ""
    onScoreChanged: scoreText.text = score
    property string text: ""

    color: cellColor

    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: cellBody.width
            height: cellBody.height
            Rectangle{
                id: maskedRect
                anchors.fill: parent
                radius: cellBody.cellBorderRadius
            }
        }
    }

    GridLayout{
        anchors.fill: parent
        rows: 2
        columns: 2
        MyRectangle{
            id: scoreTextRect
            clip: true
            Layout.row: 0
            Layout.column: 1
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            bottomBorderWidth: 1
            rightBorderWidth: 1

            color: "transparent"
            Text {
                id: scoreText
                anchors.fill: parent
                horizontalAlignment: cellBody.horizontalTextAlignment
                verticalAlignment: cellBody.verticalTextAlignment
                color: textColor
                font.pointSize: scoreFontSize
            }
        }
    }
}
