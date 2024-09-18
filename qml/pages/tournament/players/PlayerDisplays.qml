import QtQuick 6.0
import QtQuick.Layouts 1.3
import "playerDisplays.js" as Scripts
import "./playerInfoRect"

Item {
    id: playerInfoItem
    function initialize() {
        Scripts.init()
    }

    function update() {
        Scripts.updateValues()
    }

    PlayerDisplay {
        id: playerOne
        anchors.left: parent.left
        height: parent.height
        width: parent.width / 2
    }

    PlayerDisplay {
        id: playerTwo
        anchors.right: parent.right
        height: parent.height
        width: parent.width / 2
    }
}
