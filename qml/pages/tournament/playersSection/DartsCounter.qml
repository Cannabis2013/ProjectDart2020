import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "dartsCounter.js" as Scripts

Item {
        function hideDarts(number) {
                Scripts.setHiddenDarts(number)
        }

        Row {
                id: dartsLayout
                anchors.fill: parent

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
                                width: 18
                                height: 72
                                source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                                rotation: 12
                        }
                }
        }
}
