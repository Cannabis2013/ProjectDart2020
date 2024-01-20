import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "messageSection.js" as Scripts

Item {
        property string targetRow: ""
        onTargetRowChanged: row.text = Scripts.formattedTargetRow(targetRow)

        Text {
                id: row
                anchors.centerIn: parent
                width: parent.width - 12
                height: parent.height
                font.pointSize: 18
                font.weight: Font.Bold
                color: "white"
                verticalAlignment: Text.AlignBottom
                horizontalAlignment: Text.AlignLeft
                text: "Target:"
        }
}
