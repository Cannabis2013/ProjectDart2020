import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Rectangle{
    id: body

    color: "transparent"

    property int labelFontSize: 16
    onLabelFontSizeChanged: label.fontSize = labelFontSize

    property int labelFontAlignment: Qt.AlignLeft
    onLabelFontAlignmentChanged: label.horizontalTextAlignment = labelFontAlignment

    property int fontSize: 20
    onFontSizeChanged: lineEdit.fontSize = fontSize

    property int labelLeftMargin: 0
    onLabelLeftMarginChanged: label.textLeftMargin = labelLeftMargin

    FontMetrics{
        id: fontMetrics

        font.family: "Arial"
    }

    property string labelText: "Label text"
    onLabelTextChanged: label.text = labelText

    MyLabel {
        id: label

        // Font properties
        color: "black"
        fontColor: "white"
        fontSize: labelFontSize
        textLeftMargin: labelLeftMargin

        horizontalTextAlignment: labelFontAlignment

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
