import QtQuick 2.0
import QtQuick.Layouts 1.3
import "ftpSelectorsScripts.js" as SelectorScripts

Rectangle {
    id: ftpSelectorsBody
    clip: true
    color: "transparent"
    height: 5*32+4*3
    QtObject{
        id: defaultStateValues
        readonly property int defaultGameModeIndex: 0
        readonly property int defaultNumberOfThrows: 3
        readonly property int defaultKeyPointIndex: 1
        readonly property int defaultWinConditionIndex: 1
        readonly property int defaultTableHintIndex: 0
        readonly property int defaultInputModeIndex: 1
    }
    QtObject{
        id: stringModels
        property var gameModes: ["FirstToPost"]
        property var keyIdentifiers: ["Single","Double", "Tripple"]
        property var keyPoints: ["301","501","701","901"]
        property var displayHints: ["SingleView","MultiView"]
        property var inputModes: ["PointInput","ScoreInput"]
    }

    readonly property int numberOfThrows: throwSpinBox.currentValue
    readonly property int keyPoint: keyPointSelector.currentValue
    readonly property int conditionKeyCode: SelectorScripts.conditionKeyCode()
    readonly property int displayHint: SelectorScripts.tableViewHintFromString()
    readonly property int inputMode: SelectorScripts.inputModeFromString()

    GridLayout{
        anchors.fill: parent
        flow : GridLayout.TopToBottom
        rowSpacing: 3
        DefaultSpinBox {
            id: throwSpinBox
            Layout.fillWidth: true
        }
        DefaultComboBox {
            id: keyPointSelector
            Layout.fillWidth: true
            model: stringModels.keyPoints
            labelText: "Keypoint:"
        }
        DefaultComboBox {
            id: winConditionSelector
            Layout.fillWidth: true
            labelText: "Finish with:"
            model: stringModels.keyIdentifiers
        }
        DefaultComboBox {
            id: displayHintSelector
            Layout.fillWidth: true
            labelText: "Select display hint:"
            model: stringModels.displayHints
        }
        DefaultComboBox {
            id: inputModeSelector
            Layout.fillWidth: true
            labelText: "Select input mode:"
            model: stringModels.inputModes
        }
        Rectangle{
            color: "transparent"
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: SelectorScripts.initializeComponents()
}
