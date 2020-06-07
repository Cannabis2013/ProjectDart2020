import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Rectangle{
    id: body

    color: "transparent"

    property int fontSize: 20
    onFontSizeChanged: lineEdit.fontSize = fontSize

    FontMetrics{
        id: fontMetrics

        font.family: "Arial"
    }

    property string labelText: "Label text"
    onLabelTextChanged: label.text = labelText

    MyLabel {
        id: label

        color: "black"
        fontColor: "white"
        fontSize: 24

        horizontalTextAlignment: Qt.AlignHCenter

        anchors.left: parent.left

        height: parent.height
        width: 140
        text: labelText
    }

    MyTextEdit {
        id: lineEdit

        radius: 20

        fontSize: body.fontSize

        x: 120

        width: parent.width - label.width + 20
        height: parent.height
        color: "darkgray"
        fontColor: "black"
    }
    
}
