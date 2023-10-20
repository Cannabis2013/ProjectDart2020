import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
        color: "white"

        readonly property string textValue: nameInput.text

        signal clear

        onClear: nameInput.text = ""

        TextInput {
                id: nameInput
                text: textValue
                anchors.centerIn: parent
                height: parent.height - 4
                width: parent.width - 4
                Layout.fillWidth: true
                verticalAlignment: TextInput.AlignVCenter
                color: "black"
        }
}
