import QtQuick 2.15
import QtQuick.Layouts 1.3

Pad {
        id: numberPadRect

        property int padValue: -1

        color: "white"

        signal padClicked(int value)
        onPressed: scale = 0.8

        onReleased: {
                numberPadRect.padClicked(numberPadRect.padValue)
                scale = 1
        }
}
