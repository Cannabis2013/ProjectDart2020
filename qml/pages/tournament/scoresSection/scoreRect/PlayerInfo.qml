import QtQuick 2.15
import QtQuick.Layouts 1.3
import "playerInfo.js" as Scripts

Item {
        function setName(name) {
                playerName.text = name
        }

        function showCounter(status) {
                Scripts.showCounter(status)
        }

        function updateVisibleDarts(count) {
                Scripts.updateDartArrows(count)
        }

        Text {
                id: playerName
                height: 24
                width: parent.width * 0.75
                x: 6
                y: 6
                font.pointSize: 20
                font.weight: Font.Bold
                color: "white"
        }

        Item {
                id: dartsContainer
                height: 52
                width: 52
                anchors.right: parent.right
                anchors.top: parent.top
        }
}
