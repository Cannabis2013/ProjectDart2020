import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
        function setValues(winnerInfo) {
                winnerText.text = winnerInfo.winnerName
                animatedImage.source = winnerInfo.winnerImage
        }

        Text {
                id: winnerText
                width: parent.width
                anchors.top: parent.top
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
