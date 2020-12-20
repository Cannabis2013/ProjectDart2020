import QtQuick 2.0

Item {
    id: body

    signal clickEvent
    signal hoverEvent(bool sustained)
    signal pressAndHoldEvent
    signal pressedEvent(bool sustained)

    property bool enablePressAndHoldEvent: false
    property bool enableHoverEvent: true

    MouseArea
    {
        id: buttonMouseArea
        focus: true
        anchors.fill: body
        hoverEnabled: true
        onHoveredChanged: {
            hoverEvent(containsMouse);
        }

        onPressAndHold: {
            if(body.enablePressAndHoldEvent)
                body.pressAndHoldEvent();
        }

        onPressedChanged: {
            pressedEvent(containsPress);
        }

        onClicked: {
            body.clickEvent();
        }
    }
}
