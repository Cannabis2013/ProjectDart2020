import QtQuick 2.0

MyRectangle {
    id: textRect
    clip: true
    property string text: ""
    onTextChanged: textBody.text = text
    property int wrapMode: Text.NoWrap
    onWrapModeChanged: textBody.wrapMode = wrapMode
    property int horizontalAlignment: Qt.AlignHCenter
    onHorizontalAlignmentChanged: textBody.horizontalAlignment = textRect.horizontalAlignment
    property int verticalAlignment: Qt.AlignBottom
    onVerticalAlignmentChanged: textBody.verticalAlignment = textRect.verticalAlignment
    property int fontSize: 12
    onFontSizeChanged: textBody.font.pointSize = fontSize
    property color fontColor: "white"
    onFontColorChanged: textBody.color = fontColor
    Text {
        id: textBody
        anchors.fill: parent
        text: textRect.text
        horizontalAlignment: textRect.horizontalAlignment
        verticalAlignment: textRect.verticalAlignment
        font.pointSize: textRect.fontSize
        color: textRect.fontColor
        wrapMode: textRect.wrapMode
    }
}
