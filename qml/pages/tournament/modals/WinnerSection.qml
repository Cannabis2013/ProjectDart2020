import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../turn"
import "../keyPad"

Item {
        function setWinnerName(name) {
                winnerText.text = name
        }

        function setWinnerUrl(url) {
                animatedImage.source = url
        }

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                Text {
                        id: titleText
                        height: 32
                        Layout.fillWidth: true
                        text: "Winner"
                        font.pointSize: 48
                        font.weight: Font.Bold
                        horizontalAlignment: Qt.AlignHCenter
                        color: "white"
                }

                Text {
                        id: winnerText
                        height: 24
                        Layout.fillWidth: true
                        font.pointSize: 32
                        font.weight: Font.Medium
                        horizontalAlignment: Qt.AlignHCenter
                        color: "white"
                }

                AnimatedImage {
                        id: animatedImage
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                }
        }
}
