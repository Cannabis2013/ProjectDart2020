import QtQuick 2.0
import QtQuick.Layouts 1.3
import "dartsSelectorsScripts.js" as SelectorScripts

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
        property var inputModes: ["PointInput","ScoreInput"]
    }
    readonly property int keyPoint: keyPointSelector.currentValue
    readonly property int inputMode: SelectorScripts.inputModeFromString()

    GridLayout{
        anchors.fill: parent
        flow : GridLayout.TopToBottom
        rowSpacing: 3
        DefaultComboBox {
            id: keyPointSelector
            Layout.fillWidth: true
            model: stringModels.keyPoints
            labelText: "Keypoint:"
        }
        DefaultComboBox {
            id: inputModeSelector
            Layout.fillWidth: true
            labelText: "Keyboard:"
            model: stringModels.inputModes
        }
        Rectangle{
            color: "transparent"
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: SelectorScripts.initializeComponents()
}
