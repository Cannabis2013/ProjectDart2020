import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
        function setNumberOfDarts(value) {
                const children = dartsLayout.children
                for (var i = 0; i < 3; i++) {
                        const child = children[i]
                        child.visible = i < value
                }
        }

        height: 52
        width: 52

        Row {
                id: dartsLayout
                x: 6
                y: 6
                width: 38
                height: 40
                spacing: 4

                Image {
                        width: 10
                        height: 40
                        Layout.fillHeight: true
                        source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                        rotation: 12
                }

                Image {
                        width: 10
                        height: 40
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                        rotation: 12
                }

                Image {
                        width: 10
                        height: 40
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                        rotation: 12
                }
        }
}
