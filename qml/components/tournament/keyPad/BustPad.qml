import QtQuick 2.15
import QtQuick.Layouts 1.3
import "../../../components/buttons"

NewPushButton {
        id: padRect

        text: "Bust"

        color: "orange"
        radius: 0

        property int padValue: 0

        signal padClicked(string value)

        MouseArea {
                anchors.fill: parent
                onPressed: padRect.scale = 0.9
                onReleased: {
                        padRect.padClicked(padRect.padValue)
                        padRect.scale = 1
                }
        }
}
