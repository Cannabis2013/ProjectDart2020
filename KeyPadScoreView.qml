import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreViewScripts.js" as Scripts

Item {
    id: scoreViewBody
    // Font size
    property int fontSize: 28
    onFontSizeChanged: scoreViewTextEdit.font.pointSize = fontSize
    // background color and font color
    property color backgroundColor: "transparent"
    onBackgroundColorChanged: scoreViewRect.color = backgroundColor
    // Get/set value
    // Read only property
    readonly property string currentText: scoreViewTextEdit.text
    // Manipulate text
    signal appendCharacter(var c)
    onAppendCharacter: Scripts.appendCharacter(c)
    signal takeCharacter
    onTakeCharacter: Scripts.takeLastCharacter()
    signal clearView()
    onClearView: scoreViewTextEdit.clear()
    // Notify state change
    signal valueChanged(var value)
    Rectangle{
        id: scoreViewRect
        anchors.fill: parent
        color: scoreViewBody.backgroundColor
        opacity: 0.5
    }
    TextEdit{
        id: scoreViewTextEdit
        anchors.fill: parent
        text: scoreViewBody.value
        readOnly: true
        horizontalAlignment: TextEdit.AlignHCenter
        verticalAlignment: TextEdit.AlignVCenter
        font.pointSize: scoreViewBody.fontSize
        onTextChanged: valueChanged(text)
        MouseArea{
            anchors.fill: parent
            enabled: false
        }
    }
}
