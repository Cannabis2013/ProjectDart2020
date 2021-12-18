import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13
import "dsscKeyPadFactory.js" as ComponentFactory
import "dsscKeyPadScripts.js" as Scripts
DSSCKeyPadInterface {
    id: keyPadBody
    onEnableKeyPad: {
        clearPad.enabled = enable;
        submitPad.enabled = enable;
        scoreView.clearView();
    }
    onInternalHotKeyClicked: sendInput(value,0x2B)
    onInternalKeyClicked: Scripts.handleNumberPadClicked(value)
    QtObject{
        id: submitPadTextValues
        readonly property string noScoreEnted: "Bust"
        readonly property string scoreEnted: "Submit"
    }
    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: keyPadBody.width
            height: keyPadBody.height
            Rectangle{
                anchors.fill: parent
                radius: 15
            }
        }
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
            Layout.column: 1
            text: "Clear"
            backgroundColor: "white"
            textColor: "black"
            onClicked: Scripts.handleClearPadClicked()
        }
        KeyPadItem{
            id: submitPad
            Layout.row: 4
            Layout.column: 3
            text: "Bust"
            backgroundColor: "red"
            onClicked: Scripts.handleSubmitpadClicked()
        }
    }
    Component.onCompleted: Scripts.createKeyPad()
}
