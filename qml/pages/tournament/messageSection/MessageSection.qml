import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "messageSection.js" as Scripts

Item {
        property string targetRow: ""
        onTargetRowChanged: row.text = Scripts.formattedTargetRow(targetRow)

        Row {
                anchors.centerIn: parent
                width: parent.width - 12
                height: parent.height
                Text {
                        id: row
                        font.pointSize: 18
                        width: parent.width / 2
                        height: parent.height
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        text: "Target:"
                }

                Text {
                        id: message
                        font.pointSize: 18
                        width: parent.width / 2
                        height: parent.height
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        text: "Hits: S19 S19 S7"
                }
        }
}
