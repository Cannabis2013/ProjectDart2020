import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle{
    id: body

    clip: true
    property color fontColor: "black"
    onFontColorChanged: labelTitle.color = fontColor
    property int fontSize: 16
    onFontSizeChanged: labelTitle.font.pointSize = fontSize
    property color backgroundColor: "transparent"
    onBackgroundColorChanged: body.color = backgroundColor
    color: backgroundColor
    property string text: "List label"
    onTextChanged: labelTitle.text = text;
    Label{
        id: labelTitle
        color: body.fontColor
        anchors.fill: parent
        text: body.text
        font.pointSize: body.fontSize
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }
}
