import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle{
    id: labelComponentBody
    clip: true
    property color fontColor: "black"
    onFontColorChanged: labelTitle.color = fontColor
    property int fontSize: 16
    onFontSizeChanged: labelTitle.font.pointSize = fontSize
    property color backgroundColor: "transparent"
    onBackgroundColorChanged: labelComponentBody.color = backgroundColor
    color: backgroundColor
    property string text: "List label"
    onTextChanged: labelTitle.text = text;
    property int horizontalTextAlignment: Qt.AlignLeft
    Label{
        id: labelTitle
        anchors.fill: parent
        color: labelComponentBody.fontColor
        text: labelComponentBody.text
        font.pointSize: labelComponentBody.fontSize
        horizontalAlignment: labelComponentBody.horizontalTextAlignment
        verticalAlignment: Qt.AlignVCenter
    }
}
