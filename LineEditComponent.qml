import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3


Rectangle{
    id: body
    color: "transparent"
    /*
      Signals
      */
    signal textChanged
    signal enterPressed
    /*
      Properties
      */
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
    property int labelFontSize: 18
    onLabelFontSizeChanged: label.fontSize = labelFontSize
    property int labelFontAlignment: Qt.AlignLeft
    onLabelFontAlignmentChanged: label.horizontalTextAlignment = labelFontAlignment
    property int labelLeftMargin: 0
    onLabelLeftMarginChanged: label.textLeftMargin = labelLeftMargin
    property string labelText: "Label text"
    onLabelTextChanged: label.text = qsTr(labelText)
    property int fontSize: 20
    onFontSizeChanged: lineEdit.fontSize = fontSize
    property bool isNumeric: false
    onIsNumericChanged: lineEdit.numericOnly = isNumeric

    MyTextEdit {
        id: lineEdit
        //onTextChanged: body.textChanged()
        radius: body.lineEditBorderRadius
        x: parent.width / 2
        width: parent.width / 2
        height: parent.height
        color: body.backgroundColor
        fontSize: body.fontSize
        fontColor: body.fontColor
        //onEnterPressed: body.enterPressed()
    }
}
