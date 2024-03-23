import QtQuick 2.15
import QtQuick.Layouts 1.3
import "playerInfoRect.js" as Scripts

Rectangle {
        id: playerInfoRect
        clip: true
        color: "green"

        property bool expanded: false
        onExpandedChanged: playerNameDisplay.showFullName(expanded)

        function setPlayer(player) {
                Scripts.setPlayer(player)
        }

        function setValues(score, stats) {
                Scripts.setValues(score, stats)
        }

        function highlight(dartsCount) {
                Scripts.highlight(dartsCount)
        }

        function unHighlight() {
                Scripts.unHighlight()
        }

        QtObject {
                id: playerInfo
                property string fullName: ""
                property string formattedName: ""
        }

        Behavior on width {
                NumberAnimation {
                        duration: 125
                }
        }

        Text {
                id: playerName
                width: parent.width
                height: 36
                font.pointSize: 30
                font.weight: Font.Bold
                color: "white"
        }

        Text {
                id: scoreDisplayText
                anchors.bottom: statsDisplay.top
                width: parent.width
                height: 64
                font.pointSize: 100
                font.weight: Font.Bold
                color: "white"
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
        }

        CompStatsDisplay {
                id: statsDisplay
                width: parent.width
                height: 40
                anchors.bottom: parent.bottom
        }
}
