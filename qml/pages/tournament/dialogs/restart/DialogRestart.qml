import QtQuick 2.0
import QtQuick.Controls 2.5

Dialog {
        id: dialogRect
        width: 256
        height: 288
        anchors.centerIn: parent

        property string text: ""
        onTextChanged: modalText.text = text

        contentItem: Rectangle {
                color: "transparent"
                Text {
                        id: modalText
                        anchors.fill: parent
                        wrapMode: Text.WordWrap
                        color: "white"
                        font.pointSize: 16
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: qsTr("Sure you want to restart?")
                }
        }

        standardButtons: Dialog.Ok | Dialog.Cancel
}
