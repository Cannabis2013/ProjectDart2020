import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3


Rectangle{
    id: myLineEditBody

    color: "transparent"

    signal textChanged

    property int lineEditBorderRadius: 20
    onLineEditBorderRadiusChanged: lineEdit.radius = lineEditBorderRadius

    property color fontColor: "black"
    onFontColorChanged: lineEdit.fontColor = myLineEditBody.fontColor

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
        color: myLineEditBody.labelBackgroundColor

        fontColor: myLineEditBody.labelFontColor
        fontSize: labelFontSize

        textLeftMargin: labelLeftMargin
        horizontalTextAlignment: labelFontAlignment
        anchors.left: parent.left

        height: parent.height
        width: parent.width - myLineEditBody.lineEditBorderRadius

        text: labelText

        radius: labelBorderRadius
    }

    MyTextEdit {
        id: lineEdit

        onTextChanged: myLineEditBody.textChanged()

        radius: myLineEditBody.lineEditBorderRadius

        fontSize: myLineEditBody.fontSize

        x: parent.width / 2

        width: parent.width / 2
        height: parent.height

        color: myLineEditBody.backgroundColor
        fontColor: myLineEditBody.fontColor
    }

    Component.onCompleted: print(width)
}
