import QtQuick 2.0

Rectangle {
        color: "transparent"
        clip: true
        signal addItem(var item)
        signal removeItems(var indexes)
        signal itemClicked(int index)
        signal itemSelected(int index)
        signal unSelectAll
        signal clear
        signal requestUpdate
        layer.enabled: true
        Rectangle {
                id: backgroundRect
                anchors.fill: parent
                color: "white"
                opacity: 0.1
        }
}
