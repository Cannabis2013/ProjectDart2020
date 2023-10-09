import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        color: "transparent"
        clip: true

        signal appendIconLabel(string name)
        onAppendIconLabel: {
                const component = Qt.createComponent("PlayerIcon.qml")
                const object = component.createObject(iconGrid, {})
                object.setIconInitials(name[0])
        }

        GridLayout {
                anchors.fill: parent

                Rectangle {
                        Layout.fillWidth: true
                }

                GridLayout {
                        id: iconGrid
                }

                Rectangle {
                        Layout.fillWidth: true
                }
        }
}
