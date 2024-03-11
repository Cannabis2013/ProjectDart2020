import QtQuick 2.15
import QtQuick.Layouts 1.3
import "compPlayerInfos.js" as Scripts

Item {
        function initialize() {
                Scripts.init()
        }

        function setValues(jsonReport) {
                Scripts.setValues(jsonReport)
        }

        Rectangle {
                id: playerOne
                color: "green"
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2
                ColumnLayout {
                        anchors.fill: parent
                        CompPlayerInfo {
                                id: playerOneInfo
                                Layout.preferredHeight: 76
                                Layout.fillWidth: true
                        }
                        CompScoreDisplay {
                                id: playerOneScore
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                        }
                        CompStatsDisplay {
                                id: playerOneStats
                                Layout.preferredHeight: 32
                                Layout.fillWidth: true
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
                ColumnLayout {
                        anchors.fill: parent
                        CompPlayerInfo {
                                id: playerTwoInfo
                                Layout.preferredHeight: 76
                                Layout.fillWidth: true
                        }
                        CompScoreDisplay {
                                id: playerTwoScore
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                        }
                        CompStatsDisplay {
                                id: playerTwoStats
                                Layout.preferredHeight: 32
                                Layout.fillWidth: true
                        }
                }
        }
}
