import QtQuick 2.15
import QtQuick.Layouts 1.3

Item {
        property string name: ""
        onNameChanged: () => playerName.text = name

        property bool counterVisible: false
        onCounterVisibleChanged: () => dartsCounter.visible = counterVisible

        property int dartsCount: 0
        onDartsCountChanged: () => dartsCounter.setVisibleDarts(dartsCount)

        GridLayout {
                anchors.fill: parent
                Text {
                        id: playerName
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 20
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                }

                DartsCounter {
                        id: dartsCounter
                        height: 52
                        Layout.preferredWidth: 52
                }
        }
}
