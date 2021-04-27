import QtQuick 2.0

QtObject{
    property string tournamentTitle: ""
    property string determinedWinner: ""
    property int tournamentGameMode: 0x1
    property int tournamentKeyPoint: 501
    property int attempts: 3
    property int displayHint: 0x6
    property int inputHint: value
    property var assignedPlayers: []
}
