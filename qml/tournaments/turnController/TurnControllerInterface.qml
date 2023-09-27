import QtQuick 2.0

Rectangle {
        id: turnControllerInterface
        color: "transparent"
        signal start
        signal pause
        signal resume
        signal restart
        signal undo
        signal redo
        property bool startButtonEnablePressAndHold: true
        property string currentRoundIndex: ""
        property string currentPlayer: ""
        property bool leftButtonEnabled: false
        property bool rightButtonEnabled: false
        signal reset
        signal ready
        signal backendAwaitsInput
        signal backendProcessesInput
        signal backendIsStopped
        signal backendHasDeclaredAWinner
}
