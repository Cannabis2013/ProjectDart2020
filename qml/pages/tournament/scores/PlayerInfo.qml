import QtQuick 2.15
import QtQuick.Layouts 1.3

Item {
        function setName(name) {
                playerName.text = name
        }

        function showCounter(status) {
                turnCounter.visible = status
        }

        function updateCounter(count) {
                turnCounter.setNumberOfDarts(3 - count)
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

        DartsCounter {
                id: turnCounter
                anchors.right: parent.right
                anchors.top: parent.top
        }
}
