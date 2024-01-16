import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "messageSection.js" as Scripts

Item {
        property string targetRow: ""
        onTargetRowChanged: row.text = Scripts.formattedTargetRow(targetRow)

        Text {
                id: row
                anchors.fill: parent
                font.pointSize: 20
                font.weight: Font.Bold
                color: "white"
                verticalAlignment: Text.AlignVCenter
        }
}
