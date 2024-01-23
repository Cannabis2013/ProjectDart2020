import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "messageSection.js" as Scripts

Item {
        property string targetRow: ""
        onTargetRowChanged: () => Scripts.setTargetRow(targetRow)

        opacity: 0

        Behavior on opacity {
                NumberAnimation {
                        duration: 175
                }
        }

        Image {
                id: dartPlate
                source: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
                anchors.verticalCenter: parent.verticalCenter
                x: 6
                width: 40
                height: 32
        }

        Rectangle {
                id: textContainer
                color: "blue"
                x: 36
                y: 32
                height: 24
                radius: 6

                Text {
                        anchors.centerIn: parent
                        onWidthChanged: textContainer.width = width + 12
                        id: row
                        font.pointSize: 20
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                }
        }
}
