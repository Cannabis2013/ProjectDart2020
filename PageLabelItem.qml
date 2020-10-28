import QtQuick 2.0
import QtQuick.Layouts 1.3

Item
{
    id: body

    property string text: ""
    onTextChanged: pageLabel.text = text

    property color backgroundColor: "transparent"
    onBackgroundColorChanged: backgroundRect.color = backgroundColor

    property double backgroundOpacity: 1
    onBackgroundOpacityChanged: backgroundRect.opacity = backgroundOpacity

    property color fontColor: "black"
    onFontColorChanged: pageLabel.color = fontColor

    Rectangle
    {
        id: backgroundRect
        anchors.fill: body
        color: "transparent"
        opacity: body.backgroundOpacity
    }
    
    Text {
        id: pageLabel

        text: qsTr(body.text)
        
        font.pointSize: 40
        
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.fill: parent
        color: body.color
    }
}
