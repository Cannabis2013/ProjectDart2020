import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        id: padRect
        clip: true

        Layout.fillHeight: true
        Layout.fillWidth: true

        color: "grey"

        signal clicked
        signal pressed
        signal released

        Behavior on scale {
                NumberAnimation {
                        duration: 125
                }
        }

        onEnabledChanged: padRect.opacity = enabled ? 1 : 0.2

        property string text: ""
        onTextChanged: buttonText.text = qsTr(text)

        MouseArea {
                anchors.fill: parent
                onClicked: padRect.clicked()
                onPressed: padRect.pressed()
                onReleased: padRect.released()
        }

        Text {
                id: buttonText
                anchors.fill: parent
                font.pointSize: 28
                text: qsTr(padRect.text)
                color: "black"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
        }
}
