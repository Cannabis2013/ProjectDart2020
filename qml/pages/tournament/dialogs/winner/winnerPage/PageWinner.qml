import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
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

        Component.onCompleted: {
                const turnReport = JSON.parse(dartsStatus.report())
                winnerText.text = turnReport.winnerName
                animatedImage.source = turnReport.winnerImage
        }
}
