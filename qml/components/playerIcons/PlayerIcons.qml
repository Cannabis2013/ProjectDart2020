import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        color: "transparent"
        clip: true

        signal setIconLabels(var names)
        onSetIconLabels: {
                for (var i = 0; i < names.length; i++) {
                        const component = Qt.createComponent("PlayerIcon.qml")
                        const object = component.createObject(iconGrid, {})
                        object.setIconInitials(names[i])
                }
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
