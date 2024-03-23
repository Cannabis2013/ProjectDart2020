import QtQuick 2.15
import QtQuick.Layouts 1.3
import "turnCounter.js" as Scripts

Rectangle {
        color: "white"

        radius: 45

        function setHiddenDarts(count) {
                Scripts.hideDarts(count)
        }

        RowLayout {
                id: dartsLayout
                anchors.centerIn: parent
                width: 24
                height: 32
                spacing: 0

                Repeater {
                        model: 3
                        Image {
                                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                                Layout.preferredWidth: 8
                                Layout.preferredHeight: 32
                                source: "qrc:/pictures/Ressources/Pictures/dartarrow.png"
                        }
                }
        }
}
