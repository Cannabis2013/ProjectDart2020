import QtQuick 2.15
import QtQuick.Layouts 1.3
import "playerInfo.js" as Scripts

Item {

        property string name: ""
        onNameChanged: () => playerName.text = name

        property bool counterVisible: false
        onCounterVisibleChanged: () => Scripts.showCounter(counterVisible)

        property int dartsCount: 0
        onDartsCountChanged: () => Scripts.updateDartArrows(dartsCount)

        Text {
                id: playerName
                height: 24
                width: parent.width * 0.75
                x: 6
                y: 6
                font.pointSize: 20
                font.weight: Font.Bold
                color: "white"
        }

        Item {
                id: dartsContainer
                height: 52
                width: 52
                anchors.right: parent.right
                anchors.top: parent.top
        }
}
