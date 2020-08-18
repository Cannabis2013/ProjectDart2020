import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

MyRectangle{
    id: cellBody
    clip: true

    readonly property int cellHeight: cellBody.height

    property bool pointDisplayVisible: true
    onPointDisplayVisibleChanged: pointTextRect.visible = pointDisplayVisible

    property int pointDisplayWidth: 20
    onPointDisplayWidthChanged: pointTextRect.width = pointDisplayWidth

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
        seperateText(text);
    }

    color: cellColor

    function seperateText(txt)
    {
        var i = txt.indexOf(' ');
        var n = txt.length;
        var point = txt.substring(0,i);
        var score = txt.substring(i + 1,n);
        print(point);
        print(score);
        pointText.text = point;
        scoreText.text = score;
    }

    MyRectangle{
        id: pointTextRect
        anchors.top: parent.top
        anchors.left: parent.left
        width: 20
        height: parent.height/2
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
        anchors.top: parent.top
        anchors.right: parent.right
        width: parent.width - 20
        height: parent.height
        clip: true
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
