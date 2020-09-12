import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle
{
    id: body
    clip: true
    color: "transparent"
    property color fontColor: "black"
    onFontColorChanged: label.color = fontColor
    property int horizontalTextAlignment: Qt.AlignLeft
    onHorizontalTextAlignmentChanged: label.horizontalAlignment = horizontalTextAlignment
    property int verticalTextAlignment : Qt.AlignVCenter
    onVerticalTextAlignmentChanged: label.verticalAlignment = verticalTextAlignment
    property int fontSize: 12
    onFontSizeChanged: label.font.pointSize = fontSize
    property string text: "Text label"
    onTextChanged: label.text = text
    property int textLeftMargin: 0
    onTextLeftMarginChanged: label.anchors.leftMargin = textLeftMargin
    Label{
        id: label
        anchors.fill: parent
        anchors.leftMargin: textLeftMargin
        horizontalAlignment: horizontalTextAlignment
        verticalAlignment: body.verticalTextAlignment
        font.pointSize: body.fontSize
        text: body.text
        color: fontColor
    }
}
