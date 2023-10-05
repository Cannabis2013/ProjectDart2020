import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

import "../../components/buttons"

Rectangle {
        id: textFieldRect

        color: "transparent"

        signal valueChanged(string value)

        layer.enabled: true
        layer.effect: OpacityMask {
                maskSource: Rectangle {
                        width: textFieldRect.width
                        height: textFieldRect.height
                        radius: 12
                        clip: true
                }
        }

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

                NewPushButton {
                        text: "+"
                        radius: 0
                        backgroundColor: "white"
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
