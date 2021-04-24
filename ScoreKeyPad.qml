import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreKeyPadFactory.js" as ComponentFactory
import "scoreKeyPadScripts.js" as Scripts

ScoreKeyPadInterface {
    id: keyPadBody
    onEnableKeyPad: {
        clearPad.enabled = enable;
        submitPad.enabled = enable;
    }

    onInternalHotKeyClicked: sendInput(value)
    onInternalKeyClicked: Scripts.handleNumberPadClicked(value);

    QtObject{
        id: submitPadTextValues
        readonly property string noScoreEnted: "Bust"
        readonly property string scoreEnted: "Submit"
    }

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
            onValueChanged: Scripts.handleScoreViewValueChanged(value)
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
            onClicked: Scripts.handleSubmitpadClicked()
        }
    }
    Component.onCompleted: Scripts.assembleKeyPad()
}
