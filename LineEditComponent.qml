import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3


Rectangle{
    id: body

    color: "transparent"

    signal textChanged
    signal enterPressed

    property int lineEditBorderRadius: 20
    onLineEditBorderRadiusChanged: lineEdit.radius = lineEditBorderRadius

    property color fontColor: "black"
    onFontColorChanged: lineEdit.fontColor = body.fontColor

    property color backgroundColor: "white"
    onBackgroundColorChanged: lineEdit.color = backgroundColor

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
    onLabelTextChanged: label.text = qsTr(labelText)

    property int fontSize: 20
    onFontSizeChanged: lineEdit.fontSize = fontSize

    property string currentText: lineEdit.currentText

    property bool isNumeric: false
    onIsNumericChanged: lineEdit.numericOnly = isNumeric

    MyLabel {
        id: label

        // Font properties
        color: body.labelBackgroundColor

        fontColor: body.labelFontColor
        fontSize: labelFontSize

        textLeftMargin: labelLeftMargin
        horizontalTextAlignment: labelFontAlignment
        anchors.left: parent.left

        height: parent.height
        width: parent.width - body.lineEditBorderRadius

        text: labelText

        radius: labelBorderRadius
    }

    MyTextEdit {
        id: lineEdit
        onTextChanged: body.textChanged()
        radius: body.lineEditBorderRadius
        x: parent.width / 2
        width: parent.width / 2
        height: parent.height
        color: body.backgroundColor
        fontSize: body.fontSize
        fontColor: body.fontColor
        onEnterPressed: body.enterPressed()
    }

    Component.onCompleted: print(width)
}
