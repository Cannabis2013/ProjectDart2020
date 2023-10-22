import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
        id: inputRect
        color: "white"

        readonly property string textValue: nameInput.text
        property string placeholder: "placeholder"
        onPlaceholderChanged: placeholderObj.text = placeholder

        signal clear

        onClear: nameInput.text = ""

        TextInput {
                id: nameInput
                text: textValue
                anchors.centerIn: parent
                height: parent.height - 4
                width: parent.width - 4
                Layout.fillWidth: true
                inputMethodHints: Qt.ImhNoPredictiveText
                verticalAlignment: TextInput.AlignVCenter
                onDisplayTextChanged: placeholderObj.visible = nameInput.text.length <= 0

                color: "black"
                Text {
                        id: placeholderObj
                        anchors.fill: parent
                        font.weight: Font.Light
                        verticalAlignment: Text.AlignVCenter
                        text: inputRect.placeholder
                }
        }
}
