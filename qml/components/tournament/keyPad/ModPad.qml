import QtQuick 2.15
import QtQuick.Layouts 1.3
import "../../../components/buttons"

PushButton {
        id: padRect

        fontSize: 28

        radius: 0
        property string modId: ""
        property bool selected: false

        signal select(bool status)
        onSelect: {
                selected = status
                padRect.scale = selected ? 0.9 : 1
        }

        color: "darkgreen"
        fontColor: "white"

        signal modClicked(string modId)

        onClicked: {
                selected = !selected
                padRect.scale = selected ? 0.9 : 1
                modClicked(modId)
        }
}
