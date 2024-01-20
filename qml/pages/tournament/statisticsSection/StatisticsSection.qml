import QtQuick 2.15
import QtQuick.Layouts 1.3
import "statisticsSection.js" as Scripts

Rectangle {
        color: "green"
        function setStatistics(statistics) {
                Scripts.updateStatistics(statistics)
        }

        GridLayout {
                id: statisticsRects
                anchors.fill: parent
                StatisticsRect {
                        id: statisticsOne
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }

                StatisticsRect {
                        id: statisticsTwo
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }
        }
}
