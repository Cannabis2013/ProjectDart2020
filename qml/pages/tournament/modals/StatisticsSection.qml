import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../turn"
import "../keyPad"

Page {
        function setPlayerName(index, name) {
                if (index === 0)
                        playerOne.text = name
                else
                        playerTwo.text = name
        }

        function setPlayerStatistic(index, average, low, high) {
                const text = `Average: ${average}\nLow: ${low}\nHigh: ${high}`
                if (index === 0)
                        playerOneStats.text = text
                else
                        playerTwoStats.text = text
        }

        Column {
                anchors.fill: parent

                Text {
                        id: statisticsSectionTitle
                        height: 64
                        width: parent.width
                        font.pointSize: 48
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        text: qsTr("Statistics")
                }

                Text {
                        id: playerOne
                        text: "Peter Wright"
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        height: 32
                        width: parent.width
                }

                Text {
                        id: playerOneStats
                        font.pointSize: 12
                        color: "white"
                        height: 80
                        width: parent.width
                }

                Text {
                        id: playerTwo
                        text: "Van Gerwin"
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        height: 32
                        width: parent.width
                }

                Text {
                        id: playerTwoStats
                        font.pointSize: 12
                        color: "white"
                        height: 80
                        width: parent.width
                }
        }
}
