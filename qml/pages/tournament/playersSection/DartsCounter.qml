import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "dartsCounter.js" as Scripts

Item {
        function setVisibleDarts(number) {
                Scripts.updateVisibleDarts(number)
        }

        QtObject {
                id: counterRessources
                readonly property url imageUrl: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
        }

        Row {
                id: dartsLayout
                anchors.centerIn: parent
                width: 24
                height: parent.height
                layoutDirection: Qt.RightToLeft

                move: Transition {
                        NumberAnimation {
                                properties: "x,y"
                                duration: 250
                        }
                }

                populate: Transition {
                        NumberAnimation {
                                properties: "x,y"
                                duration: 350
                        }
                }

                NumberAnimation on scale {
                        from: 0.0
                        to: 1
                        duration: 175
                }

                Repeater {
                        model: 3
                        Image {
                                width: 8
                                height: 32
                                source: counterRessources.imageUrl
                                rotation: 12
                        }
                }
        }
}
