import QtQuick 2.0

Item {
    id: body
    /*
      Signals propagation
      */
    signal valueChanged(var val)
    /*
      Properties
      */
    property int contentBorderRadius: 20
    onContentBorderRadiusChanged: label.width = width - contentBorderRadius
    property color fontColor: "black"
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

    property int fontSize: 12
    onFontSizeChanged: body.children[1].children[0].fontSize = fontSize

    readonly property var currentValue : body.children[1].children[0].currentValue;

    property UserInputContent content : UserInputContent{}

    onContentChanged: {
        body.children[1].children[0] = content;
        content.anchors.fill = contentContainer
        content.valueChanged.connect(body.valueChanged);
    }

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
        width: parent.width - body.contentBorderRadius
        text: labelText
        radius: labelBorderRadius
    }
    Rectangle{
        id: contentContainer
        x: parent.width / 2
        width: parent.width / 2
        height: parent.height
        color: "transparent"
        UserInputContent{
            id: inputContent
        }
    }
}
