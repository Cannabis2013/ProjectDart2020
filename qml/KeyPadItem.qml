import QtQuick 2.0
import QtQuick.Layouts 1.3

PushButton {
        property int type: 0x1
        property int padValue: -1
        signal keyPadClicked(int value)
        onClicked: keyPadClicked(padValue)
        Layout.fillHeight: true
        Layout.fillWidth: true
        backgroundColor: "black"
        textColor: "white"
        fontSize: 24
        buttonRadius: 0
        pressedScale: 0.95
        enabled: false
}
