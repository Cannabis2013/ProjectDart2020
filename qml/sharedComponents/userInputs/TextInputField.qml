import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls

Rectangle {
        id: textFieldRect

        color: "transparent"

        signal valueChanged(string value)

        property string placeholder: "placeholder"
        onPlaceholderChanged: nameInputBox.placeholder = placeholder

        Keys.onReturnPressed: {
                const value = nameInputBox.textValue
                if (value == "")
                        return
                valueChanged(value)
                nameInputBox.clear()
        }

        Keys.onEnterPressed: {
                const value = nameInputBox.textValue
                if (value == "")
                        return
                valueChanged(value)
                nameInputBox.clear()
        }

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.LeftToRight
                columnSpacing: 0

                Rectangle {
                        width: 6
                }

                TextInputBox {
                        id: nameInputBox
                        Layout.fillWidth: true
                        height: 32
                        placeholder: textFieldRect.placeholder
                }

                Rectangle {
                        width: 1
                }

                Button {
                        background: Rectangle {
                                color: "white"
                                anchors.fill: parent
                        }

                        Layout.fillHeight: true
                        width: 32

                        Text {
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "+"
                                font.pointSize: 20
                                font.weight: Font.Bold
                        }

                        onClicked: {
                                const value = nameInputBox.textValue
                                if (value == "")
                                        return
                                valueChanged(value)
                                nameInputBox.clear()
                        }
                }
        }
}
