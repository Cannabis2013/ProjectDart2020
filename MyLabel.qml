import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Rectangle
{
    id: body

    property color fontColor: "black"
    onFontColorChanged: label.color = fontColor

    property int horizontalTextAlignment: Qt.AlignLeft
    onHorizontalTextAlignmentChanged: label.horizontalAlignment = horizontalTextAlignment

    property int fontSize: 24
    onFontSizeChanged: label.font.pointSize = fontSize

    property string text: "Text label"
    onTextChanged: label.text = text

    Label{
        id: label
        anchors.fill: parent

        horizontalAlignment: horizontalTextAlignment
        verticalAlignment: Qt.AlignVCenter

        font.pointSize: fontSize

        text: body.text
        color: fontColor


    }
}
