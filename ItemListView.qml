import QtQuick 2.0
import QtGraphicalEffects 1.13
Rectangle {
    color: "transparent"
    clip: true
    signal addItem(var item)
    signal removeItems(var indexes)
    signal itemClicked(int index)
    signal itemSelected(int index)
    signal unSelectAll()
    signal clear()
    signal requestUpdate()
    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: listComponentBody.width
            height: listComponentBody.height

            Rectangle{
                anchors.fill: parent
                radius: listComponentBody.radius
            }
        }
    }
    Rectangle{
        id: backgroundRect
        anchors.fill: parent
        color: "white"
        opacity: 0.1
    }
}
