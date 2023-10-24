import QtQuick 2.15
import QtQuick.Layouts 1.3

Pad {
        id: numberPadRect

        property int padValue: -1

        signal padClicked(int value)
        signal padLongClicked
        onPressed: numberPadRect.color = "red"

        ColorAnimation on color {
                id: pushAnimation
                from: "red"
                to: numberPadRect.backgroundColor
                duration: 750
                loops: 1
                running: false
        }

        onReleased: {
                if (pressInfo.isLongPress) {
                        pressInfo.isLongPress = false
                        return
                }
                numberPadRect.padClicked(numberPadRect.padValue)
                pushAnimation.start()
        }
        onPressAndHold: {
                pressInfo.isLongPress = true
                numberPadRect.padLongClicked()
        }

        QtObject {
                id: pressInfo
                property bool isLongPress: false
        }
}
