import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "pageStatistics.js" as Scripts

Page {
        Text {
                id: pageTitle
                height: 64
                width: parent.width
                font.pointSize: 48
                color: "white"
                text: qsTr("Game stats")
        }

        CompStatistics {
                id: playerOneItem
                anchors.top: pageTitle.bottom
                anchors.topMargin: 24
                width: parent.width
        }

        CompStatistics {
                id: playerTwoItem
                anchors.top: playerOneItem.bottom
                width: parent.width
        }

        Component.onCompleted: Scripts.init()
}
