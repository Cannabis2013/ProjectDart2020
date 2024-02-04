import QtQuick 2.15

import "compPlayerInfo"
import "compScoreDisplay"
import "compStatsDisplay"
import "compPlayerInfos.js" as Scripts

Item {
        function initialize() {
                Scripts.init()
        }

        function setValues(turnReport) {
                Scripts.setValues(turnReport)
        }

        Rectangle {
                id: playerOne
                color: "green"
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2
                Column {
                        anchors.fill: parent
                        CompPlayerInfo {
                                id: playerOneInfo
                                width: parent.width
                        }
                        CompScoreDisplay {
                                id: playerOneScore
                                width: parent.width
                        }
                        CompStatsDisplay {
                                id: playerOneStats
                                width: parent.width
                        }
                }
        }

        Rectangle {
                id: playerTwo
                color: "green"
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2
                Column {
                        anchors.fill: parent
                        CompPlayerInfo {
                                id: playerTwoInfo
                                width: parent.width
                        }
                        CompScoreDisplay {
                                id: playerTwoScore
                                width: parent.width
                        }
                        CompStatsDisplay {
                                id: playerTwoStats
                                width: parent.width
                        }
                }
        }
}
