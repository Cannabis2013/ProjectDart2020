import QtQuick 2.15
import QtQuick.Layouts 1.3
import "../../../components/buttons"

Pad {
        id: padRect

        radius: 0
        property int padValue: -1

        signal padClicked(int value)

        ColorAnimation on color {
                id: pushAnimation
                from: "red"
                to: padRect.backgroundColor
                duration: 750
                loops: 1
                running: false
        }

        MouseArea {
                anchors.fill: parent
                onPressed: padRect.color = "red"

                onReleased: {
                        padRect.padClicked(padRect.padValue)
                        padRect.scale = 1
                        pushAnimation.start()
                }
        }
}
