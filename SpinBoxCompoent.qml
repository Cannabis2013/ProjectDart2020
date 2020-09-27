import QtQuick 2.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.13

Rectangle{
    id: body
    color: "transparent"
    clip: true

    /*
      Signals
      */
    signal textChanged
    signal enterPressed
    /*
      Properties
      */
    property int lineEditBorderRadius: 20
    property color fontColor: "black"
    onFontColorChanged: lineEdit.fontColor = body.fontColor
    property int labelBorderRadius: 20
    onLabelBorderRadiusChanged: label.radius = labelBorderRadius
    property color labelBackgroundColor: "black"
    onLabelBackgroundColorChanged: label.color = labelBackgroundColor
    property color labelFontColor: "black"
    onLabelFontColorChanged: label.fontColor = labelFontColor
    property int labelFontSize: 18
    onLabelFontSizeChanged: label.fontSize = labelFontSize
    property int labelFontAlignment: Qt.AlignLeft
    onLabelFontAlignmentChanged: label.horizontalTextAlignment = labelFontAlignment
    property int labelLeftMargin: 0
    onLabelLeftMarginChanged: label.textLeftMargin = labelLeftMargin
    property string labelText: "Label text"
    onLabelTextChanged: label.text = qsTr(labelText)
    property int fontSize: 20
    onFontSizeChanged: spinBox.font.pointSize = fontSize
    readonly property string currentText: lineEdit.currentText
    property bool isNumeric: false
    onIsNumericChanged: lineEdit.numericOnly = isNumeric
    readonly property int currentValue: spinBox.value
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
    SpinBox {
        id: spinBox
        layer.enabled: true
        layer.effect: OpacityMask{
            maskSource: Item {
                width: spinBox.width
                height: spinBox.height
                Rectangle{
                    anchors.fill: parent
                    radius: 20
                }
            }
        }
        x: parent.width / 2
        width: parent.width / 2
        height: parent.height
        font.pointSize: body.fontSize
        value: 3
    }
}
