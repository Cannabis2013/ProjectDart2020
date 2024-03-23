import QtQuick 2.15
import QtQuick.Layouts 1.3
import "compPlayerInfos.js" as Scripts
import "./playerInfoRect"
import "./turnCounter"

Item {
        id: playerInfoItem
        function initialize() {
                Scripts.init()
        }

        function update() {
                Scripts.updateValues()
        }

        PlayerInfoRect {
                id: playerOne
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                width: parent.width / 2
                MouseArea {
                        anchors.fill: parent
                        onClicked: Scripts.expandPlayerOne()
                }
        }

        PlayerInfoRect {
                id: playerTwo
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2
                MouseArea {
                        anchors.fill: parent
                        onClicked: Scripts.expandPlayerTwo()
                }
        }

        TurnCounter {
                id: turnCounter
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.horizontalCenter: parent.horizontalCenter
                height: 48
                width: 48
        }
}
