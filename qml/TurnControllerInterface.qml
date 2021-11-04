import QtQuick 2.0
Item {
    clip: true
    signal startButtonClicked
    signal pauseButtonClicked
    signal resumeButtonClicked
    signal restartButtonClicked
    signal leftButtonClicked
    signal rightButtonClicked
    signal leftButtonPressAndHoldClicked
    signal rightButtonPressAndHoldClicked
    property bool startButtonEnablePressAndHold : true
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
    function createPlayerString()
    {
        var player = currentPlayer;
        var round = currentRoundIndex;
        var string = `${player} (${round})`;
        if(string !== "")
            return string;
        return "Player (round)";
    }
}
