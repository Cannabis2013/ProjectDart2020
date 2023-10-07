import QtQuick 2.15
import QtQuick.Layouts 1.3
import "../../../components/buttons"

NewPushButton {
        id: padRect

        text: "50"

        color: "red"
        radius: 0

        property int padValue: 50

        signal padClicked(int value)

        MouseArea {
                anchors.fill: parent
                onPressed: padRect.scale = 0.9
                onReleased: {
                        padRect.padClicked(padRect.padValue)
                        padRect.scale = 1
                }
        }
}
