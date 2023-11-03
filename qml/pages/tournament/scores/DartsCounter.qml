import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Rectangle {
        color: "transparent"

        function setNumberOfDarts(value) {
                const children = dartsLayout.children
                for (var i = 0; i < 3; i++) {
                        const child = children[i]
                        child.visible = i < value
                }
        }

        GridLayout {
                id: dartsLayout
                anchors.fill: parent
                columnSpacing: 4

                Rectangle {
                        Layout.fillWidth: true
                }

                Image {
                        Layout.minimumWidth: parent.height / 4
                        Layout.maximumWidth: parent.height / 4
                        Layout.fillHeight: true
                        source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                }

                Image {
                        Layout.minimumWidth: parent.height / 4
                        Layout.maximumWidth: parent.height / 4
                        Layout.fillHeight: true
                        source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                }

                Image {
                        Layout.minimumWidth: parent.height / 4
                        Layout.maximumWidth: parent.height / 4
                        Layout.fillHeight: true
                        source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                }

                Rectangle {
                        Layout.fillWidth: true
                }
        }
}
