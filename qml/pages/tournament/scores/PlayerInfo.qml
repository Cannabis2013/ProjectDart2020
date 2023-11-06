import QtQuick 2.15
import QtQuick.Layouts 1.3

Item {
        function setName(name) {
                playerName.text = name
        }

        function showCounter(status) {
                const dartsCounter = dartsContainer.children[0]
                if (status && !dartsCounter) {
                        const comp = Qt.createComponent("./counter/DartsCounter.qml")
                        const obj = comp.createObject(dartsContainer)
                } else if (!status && dartsCounter) {
                        dartsCounter.destroy()
                }
        }

        function updateVisibleDarts(count) {
                const turnCounter = dartsContainer.children[0]
                turnCounter.setVisibleDarts(count)
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
