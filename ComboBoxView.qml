import QtQuick 2.0

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle{
    id: comboBoxViewBody

    color: "transparent"

    property int borderRadius: 20
    onBorderRadiusChanged: lineEdit.radius = borderRadius

    property int labelBorderRadius: 20
    onLabelBorderRadiusChanged: label.radius = labelBorderRadius

    property color labelBackgroundColor: "black"
    onLabelBackgroundColorChanged: label.color = labelBackgroundColor

    property color labelFontColor: "black"
    onLabelFontColorChanged: label.fontColor = labelFontColor

    property int labelFontSize: 16
    onLabelFontSizeChanged: label.fontSize = labelFontSize

    property int labelFontAlignment: Qt.AlignLeft
    onLabelFontAlignmentChanged: label.horizontalTextAlignment = labelFontAlignment

    property int labelLeftMargin: 0
    onLabelLeftMarginChanged: label.textLeftMargin = labelLeftMargin

    property string labelText: "Label text"
    onLabelTextChanged: label.text = labelText

    property string currentText: comboBox.currentSelectedText()

    property var stringModel: [""]
    onStringModelChanged: comboBox.stringModel = stringModel

    function setModel(strings)
    {
        comboBox.setModel(strings);
    }

    MyLabel
    {
        id: label

        // Font properties
        color: comboBoxViewBody.labelBackgroundColor

        fontColor: "white"
        fontSize: comboBoxViewBody.labelFontSize

        textLeftMargin: comboBoxViewBody.labelLeftMargin

        horizontalTextAlignment: labelFontAlignment

        anchors.left: parent.left

        height: parent.height
        width: parent.width / 2 + comboBoxViewBody.borderRadius

        text: labelText

        radius: comboBoxViewBody.labelBorderRadius
    }

    ComboBoxComponent {
        id: comboBox

        x: parent.width / 2

        height: parent.height
        width: parent.width / 2

        radius: comboBoxViewBody.borderRadius

        PropertyAnimation on width {
            from: 0
            to: parent.width / 2

            duration: 300

            easing.type: Easing.OutBounce
        }
    }

}
