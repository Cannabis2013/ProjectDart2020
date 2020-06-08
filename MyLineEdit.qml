import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Rectangle{
    id: body

    color: "transparent"

    property int borderRadius: 20
    onBorderRadiusChanged: lineEdit.radius = borderRadius

    property color fontColor: "black"
    onFontColorChanged: lineEdit.fontColor = body.fontColor

    property color backgroundColor: "white"
    onBackgroundColorChanged: lineEdit.color = backgroundColor

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
        width: parent.width / 2 + body.borderRadius

        text: labelText


    }

    MyTextEdit {
        id: lineEdit

        radius: body.borderRadius

        fontSize: body.fontSize

        x: parent.width / 2

        width: parent.width / 2
        height: parent.height

        color: body.backgroundColor
        fontColor: body.fontColor

        PropertyAnimation on width {
            from: 0
            to: parent.width / 2

            duration: 300

            easing.type: Easing.OutBounce
        }
    }
    
}
