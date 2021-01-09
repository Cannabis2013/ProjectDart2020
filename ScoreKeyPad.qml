import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreKeyPadFactory.js" as ComponentFactory
import "scoreKeyPadScripts.js" as Scripts

KeyPadInterface {
    id: keyPadBody
    onEnableKeyPad: {
        clearPad.enabled = enable;
        submitPad.enabled = enable;
    }

    onInternalHotKeyClicked: sendInput(value,1)
    onInternalKeyClicked: Scripts.handleNumberPadClicked(value);

    GridLayout{
        id: keyPadLayout
        anchors.fill: parent
        rowSpacing: 1
        columnSpacing: 1
        rows: 5
        columns: 5

        KeyPadScoreView {
            id: scoreView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.row: 0
            Layout.column: 2
            backgroundColor: "white"
        }
        KeyPadItem{
            id: clearPad
            Layout.row: 4
            Layout.column: 0
            text: "Clear"
            backgroundColor: "white"
            textColor: "black"
            onClicked: Scripts.handleClearPadClicked()
        }
        KeyPadItem{
            id: submitPad
            Layout.row: 4
            Layout.column: 4
            text: "Bust"
            backgroundColor: "red"
        }
    }
    Component.onCompleted: Scripts.assembleKeyPad()
}
