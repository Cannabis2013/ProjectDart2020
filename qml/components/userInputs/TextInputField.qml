import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls

Rectangle {
        id: textFieldRect

        color: "transparent"

        signal valueChanged(string value)

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
                Text {
                        height: 32
                        width: 64
                        font.pointSize: 12
                        color: "white"
                        text: "Enter name"
                }

                Rectangle {
                        width: 6
                }

                TextInputBox {
                        id: nameInputBox
                        Layout.fillWidth: true
                        height: 32
                }

                Rectangle {
                        width: 1
                }

                Button {
                        text: "+"
                        background: Rectangle {
                                color: "white"
                        }

                        height: 32
                        width: 32
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
