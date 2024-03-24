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
                anchors.left: parent.left
                height: parent.height
                width: parent.width / 2
                MouseArea {
                        anchors.fill: parent
                        onClicked: Scripts.expandPlayerOne()
                }
        }

        PlayerInfoRect {
                id: playerTwo
                anchors.right: parent.right
                height: parent.height
                width: parent.width / 2
                MouseArea {
                        anchors.fill: parent
                        onClicked: Scripts.expandPlayerTwo()
                }
        }
}
