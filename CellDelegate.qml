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
    
    property string text: ""
    onTextChanged: {
        processText(text);
    }

    color: cellColor

    function processText(txt)
    {
        var i = txt.indexOf(' ');
        var n = txt.length;
        var point = txt.substring(0,i);
        var score = txt.substring(i + 1,n);
        pointText.text = point;
        scoreText.text = score;
    }

    GridLayout{
        anchors.fill: parent
        rows: 2
        columns: 2

        MyRectangle{
            id: pointTextRect
            Layout.row: 0
            Layout.column: 0
            Layout.preferredWidth: cellBody.pointDisplayWidth
            Layout.preferredHeight: cellBody.pointDisplayHeight
            Layout.alignment: Qt.AlignTop
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
