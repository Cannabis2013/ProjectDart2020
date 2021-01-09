import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreViewScripts.js" as Scripts

Item {
    id: scoreViewBody
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
        font.pointSize: 32
        onTextChanged: valueChanged(text)
        MouseArea{
            anchors.fill: parent
            enabled: false
        }
    }
}
