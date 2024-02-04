import QtQuick 2.15
import QtQuick.Layouts 1.3
import "compPlayerInfo.js" as Scripts

Item {
        id: infoRect

        function setPlayer(player) {
                Scripts.setPlayer(player)
        }

        function hideDarts(count) {
                Scripts.setHiddenDarts(count)
        }

        Text {
                id: playerName
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 6
                anchors.rightMargin: 6
                height: 36
                font.pointSize: 30
                font.weight: Font.Bold
                color: "white"
        }

        Text {
                id: playerNationality
                anchors.left: parent.left
                anchors.leftMargin: 6
                anchors.bottom: parent.bottom
                height: 32
                width: 64
                font.pointSize: 20
                verticalAlignment: Text.AlignBottom
                color: "white"
        }

        Row {
                id: dartsLayout
                height: 40
                width: 30
                anchors.right: parent.right
                anchors.rightMargin: 12
                anchors.bottom: parent.bottom

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
                                width: 10
                                height: 40
                                source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                                rotation: 12
                        }
                }
        }
}
