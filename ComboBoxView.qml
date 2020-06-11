import QtQuick 2.0

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle{
    id: body

    color: "transparent"

    property int borderRadius: 20
    onBorderRadiusChanged: lineEdit.radius = borderRadius

    property int labelBorderRadius: 20
    onLabelBorderRadiusChanged: label.radius = labelBorderRadius

    property color labelBackgroundColor: "black"
    onLabelBackgroundColorChanged: label.color = labelBackgroundColor

    property int labelFontSize: 16
    onLabelFontSizeChanged: label.fontSize = labelFontSize

    property int labelFontAlignment: Qt.AlignLeft
    onLabelFontAlignmentChanged: label.horizontalTextAlignment = labelFontAlignment

    property int labelLeftMargin: 0
    onLabelLeftMarginChanged: label.textLeftMargin = labelLeftMargin

    property string labelText: "Label text"
    onLabelTextChanged: label.text = labelText


    function setModel(strings)
    {
        comboBox.setModel(strings)
    }

    MyLabel
    {
        id: label

        // Font properties
        color: body.labelBackgroundColor

        fontColor: "white"
        fontSize: body.labelFontSize

        textLeftMargin: body.labelLeftMargin

        horizontalTextAlignment: labelFontAlignment

        anchors.left: parent.left

        height: parent.height
        width: parent.width / 2 + body.borderRadius

        text: labelText

        radius: body.labelBorderRadius
    }

    MyCombBoxComponent {
        id: comboBox

        x: parent.width / 2

        height: parent.height
        width: parent.width / 2

        radius: body.borderRadius

        PropertyAnimation on width {
            from: 0
            to: parent.width / 2

            duration: 300

            easing.type: Easing.OutBounce
        }
    }

}
