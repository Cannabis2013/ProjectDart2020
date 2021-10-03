import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0
import QtGraphicalEffects 1.13

MyRectangle{
    id: scoreTextRect
    clip: true
    anchors.fill: parent
    color: "green"
    bottomBorderWidth: 1
    topBorderWidth: 1
    rightBorderWidth: 1
    property string text: ""
    onTextChanged: scoreText.text = text
    GridLayout{
        anchors.fill: parent
        columns: 3
        rows: 3
        Rectangle
        {
            id: leftPadding
            Layout.column: 0
            Layout.row: 1
            width: 2
        }
        Rectangle{
            id: upperPadding
            Layout.column: 0
            Layout.row: 0
            Layout.columnSpan: 3
            width: 0
        }
        Rectangle
        {
            id: rightPadding
            Layout.column: 2
            Layout.row: 1
            width: 0
        }

        Rectangle
        {
            id: bottomPadding
            Layout.column: 0
            Layout.row: 2
            Layout.columnSpan: 3
            width: 0
        }
        Text {
            Layout.column: 1
            Layout.row: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: scoreText
            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignVCenter
            color: "white"
            font.pointSize: 20
            text: scoreTextRect.text
        }
    }

}
