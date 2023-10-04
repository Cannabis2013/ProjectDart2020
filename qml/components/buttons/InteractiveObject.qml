import QtQuick 2.0

Item {
        id: body
        signal clickEvent
        signal hoverEvent(bool sustained)
        signal pressAndHoldEvent
        signal pressedEvent(bool sustained)
        property bool enablePressAndHoldEvent: false
        property bool enableHoverEvent: true
        QtObject {
                id: internalEventHandler
                function handlePressEvent() {
                        if (isPressed) {
                                isPressed = false
                                return false
                        }
                        isPressed = true
                        return true
                }
                property bool isPressed: false
        }
        MouseArea {
                id: buttonMouseArea
                focus: true
                anchors.fill: body
                hoverEnabled: true
                onHoveredChanged: {
                        body.hoverEvent(containsMouse)
                }
                onPressAndHold: {
                        if (body.enablePressAndHoldEvent)
                                body.pressAndHoldEvent()
                }
                onPressedChanged: {
                        body.pressedEvent(internalEventHandler.handlePressEvent(
                                                  ))
                }
                onClicked: {
                        body.clickEvent()
                }
        }
}
