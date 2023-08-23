import QtQuick 2.0

Item {
        id: body

        signal valueChanged(var val)

        property int contentBorderRadius: 0
        onContentBorderRadiusChanged: label.width = width - contentBorderRadius
        property color fontColor: "black"
        property int labelBorderRadius: 0
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
        property bool showLabel: true
        onShowLabelChanged: label.visible = showLabel
        // Set content value
        property var contentValue: content.currentValue
        onContentValueChanged: content.setValue(contentValue)
        property int fontSize: 12
        onFontSizeChanged: inputContent.fontSize = fontSize

        readonly property var currentValue: content.currentValue
        property int currentIndex: content.currentIndex
        onCurrentIndexChanged: content.currentIndex = body.currentIndex
        property UserInputContent content: UserInputContent {}
        onContentChanged: {
                body.children[1].children[0] = content
                content.anchors.fill = contentContainer
                content.valueChanged.connect(body.valueChanged)
        }

        MyLabel {
                id: label
                visible: body.showLabel
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
        Rectangle {
                id: contentContainer
                x: parent.width / 2
                width: parent.width / 2
                height: parent.height
                color: "transparent"
                UserInputContent {}
        }
}
