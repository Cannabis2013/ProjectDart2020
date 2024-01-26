import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
        function setWinnerName(name) {
                winnerText.text = name
        }

        function setWinnerUrl(url) {
                animatedImage.source = url
        }

        Text {
                id: titleText
                anchors.top: parent.top
                height: 48
                width: parent.width
                text: "Winner"
                font.pointSize: 48
                font.weight: Font.Bold
                horizontalAlignment: Qt.AlignHCenter
                color: "white"
        }

        Text {
                id: winnerText
                width: parent.width
                anchors.top: titleText.bottom
                anchors.topMargin: 12
                font.pointSize: 32
                font.weight: Font.Medium
                horizontalAlignment: Qt.AlignHCenter
                color: "white"
                wrapMode: Text.WordWrap
        }

        AnimatedImage {
                id: animatedImage
                width: parent.width
                anchors.top: winnerText.bottom
                anchors.topMargin: 12
                anchors.bottom: parent.bottom
        }
}
