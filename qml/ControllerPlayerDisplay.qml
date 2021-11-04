import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
Rectangle{
    clip: true
    color: "transparent"
    width: 128
    signal clear()
    onClear: textLabel.text = ""
    property string text: ""
    onTextChanged: textLabel.text = text
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        Label{
            id: textLabel
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            text: currentPlayer
            font.pointSize: 20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
