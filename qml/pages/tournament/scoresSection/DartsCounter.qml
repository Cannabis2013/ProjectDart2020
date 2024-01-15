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

                x: 6
                y: 6
                width: 38
                height: 40
                spacing: 4

                NumberAnimation on scale {
                        from: 0.0
                        to: 1
                        duration: 175
                }

                Image {
                        width: 10
                        height: 40
                        source: counterRessources.imageUrl
                        rotation: 12
                }

                Image {
                        width: 10
                        height: 40
                        source: counterRessources.imageUrl
                        rotation: 12
                }

                Image {
                        width: 10
                        height: 40
                        source: counterRessources.imageUrl
                        rotation: 12
                }
        }
}
