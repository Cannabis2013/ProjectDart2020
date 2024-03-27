import QtQuick 2.9
import QtQuick.Controls 2.15
import "../templates"
import "setupPage2.js" as Scripts

PageWithHeader {
        anchors.fill: parent
        Label {
                id: labelMode
                text: "Mode:"
                width: 64
                height: 32
                font.pixelSize: 20
                verticalAlignment: Text.AlignVCenter
        }

        ComboBox {
                id: selectorMode
                anchors.left: labelMode.right
                anchors.leftMargin: 6
                width: 192
                height: 32
                flat: true
                model: ["Novice", "Professional"]
        }
}
