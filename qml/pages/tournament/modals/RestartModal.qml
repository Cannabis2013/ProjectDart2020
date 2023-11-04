import QtQuick 2.0
import QtQuick.Controls

Dialog {
        id: dialogRect
        width: 256
        height: 288
        anchors.centerIn: parent

        contentItem: Rectangle {
                color: "transparent"
                Text {
                        anchors.fill: parent
                        text: qsTr("Sure you want to restart?")
                        wrapMode: Text.WordWrap
                        color: "white"
                        font.pointSize: 24
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                }
        }

        standardButtons: Dialog.Ok | Dialog.Cancel
}
