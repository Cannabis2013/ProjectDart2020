import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

MyRectangle{
    id: cellBody
    clip: true

    readonly property int cellHeight: cellBody.height

    property bool pointDisplayVisible: false
    onPointDisplayVisibleChanged: pointTextRect.visible = pointDisplayVisible

    property int pointDisplayWidth: 20
    onPointDisplayWidthChanged: pointTextRect.width = pointDisplayWidth

    property int pointDisplayHeight: 20
    onPointDisplayHeightChanged: pointTextRect.Height = pointDisplayHeight

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
            horizontalAlignment: cellBody.horizontalTextAlignment
            verticalAlignment: cellBody.verticalTextAlignment
            color: textColor
            font.pointSize: scoreFontSize
        }
    }
    MyRectangle{
        id: pointTextRect
        x: 5
        y: 5
        width: cellBody.pointDisplayWidth
        height:  cellBody.pointDisplayHeight
        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        clip: true
        visible: cellBody.pointDisplayVisible
        color: "blue"
        Text {
            id: pointText
            anchors.fill: parent
            horizontalAlignment: cellBody.horizontalTextAlignment
            verticalAlignment: cellBody.verticalTextAlignment
            color: textColor
            font.pointSize: cellBody.pointFontSize
        }
    }
}
