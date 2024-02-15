import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "compStatistics.js" as Scripts

Item {
        height: 136

        function setStatistics(statistics) {
                Scripts.setStatistics(statistics)
        }

        function setScore(score) {
                Scripts.setScore(score)
        }

        Text {
                id: playerName
                fontSizeMode: Text.Fit
                font.pointSize: 64
                font.weight: Font.Bold
                color: "white"
                height: 24
                width: 140
        }

        Text {
                id: playerStats
                font.pointSize: 16
                color: "white"
                anchors.top: playerName.bottom
                height: 112
                width: 140
        }

        Text {
                id: playerScore
                clip: true
                anchors.right: parent.right
                height: 136
                width: parent.width - 140
                verticalAlignment: Text.AlignTop
                fontSizeMode: Text.VerticalFit
                font.pointSize: 112
                color: "white"
        }
}
