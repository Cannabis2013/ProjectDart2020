import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

MyRectangle{
    id: cellDelegate
    clip: true

    readonly property int cellHeight: cellDelegate.height

    property color cellColor: "white"
    onCellColorChanged: cellDelegate.color = cellColor

    property color textColor: "white"
    onTextColorChanged: scoreText = textColor

    property int pointFontSize: 16
    onPointFontSizeChanged: pointText.font.pointSize = pointFontSize

    property int scoreFontSize: 16
    onScoreFontSizeChanged: scoreText.font.pointSize = scoreFontSize

    property double cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.border.width = cellBorderWidth

    property color cellBorderColor: "black"
    onCellBorderColorChanged: cellDelegate.border.color = cellBorderColor

    property int horizontalTextAlignment: Text.AlignHCenter
    onHorizontalTextAlignmentChanged: scoreText.horizontalAlignment = horizontalTextAlignment

    property int verticalTextAlignment: Text.AlignVCenter
    onVerticalTextAlignmentChanged: scoreText.verticalAlignment = verticalTextAlignment
    bottomBorderWidth: 1
    rightBorderWidth: 1
    
    implicitWidth: 25
    implicitHeight: 25

    property string point: ""
    onPointChanged: pointText.text = point;

    property string score: ""
    onScoreChanged: scoreText.text = score
    
    property string text: ""
    onTextChanged: {
        setText(text);
    }

    color: cellColor

    function setText(txt)
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
        height: parent.height
        bottomBorderWidth: 1
        clip: true

        color: "blue"
        Text {
            id: pointText
            anchors.fill: parent
            horizontalAlignment: cellDelegate.horizontalTextAlignment
            verticalAlignment: cellDelegate.verticalTextAlignment
            color: textColor
            font.pointSize: cellDelegate.pointFontSize
            text: cellDelegate.point
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

        color: "purple"
        Text {
            id: scoreText
            anchors.fill: parent
            horizontalAlignment: cellDelegate.horizontalTextAlignment
            verticalAlignment: cellDelegate.verticalTextAlignment
            text: cellDelegate.score
            color: textColor
            font.pointSize: scoreFontSize
        }
    }
}
