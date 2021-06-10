import QtQuick 2.4
import QtQuick.Layouts 1.3

Content{
    id: body
    clip: true

    signal createTournamentClicked
    signal dartsPointSingleAttemptInitialized
    signal dartsScoreMultiAttemptIsInitialized
    signal manageButtonClicked
    signal requestTournaments
    signal requestDeleteTournaments(var indexes)
    signal sendClickedTournamentIndex(int index)

    QtObject{
        id: currentValues
        property int currentIndex: -1
    }

    function recieveTournaments(json)
    {
        var jsonTournaments= JSON.parse(json);
        var jsonLength = jsonTournaments.length;
        for(var i = 0;i < jsonLength;++i)
        {
            var jsonTournament = jsonTournaments[i];
            var gameMode = jsonTournament["gameMode"];
            var title = jsonTournament["title"];
            var winnerName = jsonTournament["winnerName"];
            var assignedPlayerNames = jsonTournament["assignedPlayerNames"];
            var assignedPlayersCount = assignedPlayerNames.length;
            tournamentListView.addItemModel(
                        {
                            "type" : "tournament",
                            "gameMode" : translateGameModeFromHex(gameMode),
                            "tournamentTitle" : title,
                            "winner" : winnerName,
                            "playersCount" : assignedPlayersCount
                        });
        }
    }

    function translateGameModeFromHex(gameMode)
    {
        if(gameMode === TournamentContext.darts)
            return "First to post"
    }
    onRequestUpdate: {
        requestTournaments();
    }

    GridLayout
    {
       anchors.fill: parent

       columnSpacing: 0
       rowSpacing: 4

       flow: GridLayout.TopToBottom

       DefaultTournamentListView {
           id: tournamentListView
           Layout.fillWidth: true
           Layout.fillHeight: true
           allowMultipleSelections: false
           allowCheckState: false
           instantSelectEnabled: true
           itemTitleTextColor: ThemeContext.tournamentListViewTextColor
           itemDescriptionFontColor: ThemeContext.tournamentListViewTextColor
           titleTextColor: ThemeContext.tournamentListViewTextColor
           onItemClicked: sendClickedTournamentIndex(index)
       }
       GridLayout{
           flow: GridLayout.LeftToRight
           columnSpacing: 2
           Rectangle{
               Layout.fillWidth: true
           }
           CRUDButton{
               id: manageButton
               text: "Manage"
               onClicked: manageButtonClicked()
           }
       }
    }
    Component.onCompleted: {
        body.requestTournaments.connect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
        applicationInterface.sendTournaments.connect(recieveTournaments);
        body.sendClickedTournamentIndex.connect(applicationInterface.handleSetCurrentTournamentRequest);
        applicationInterface.dartsPointMultiColumnsInitialized.connect(dartsPointSingleAttemptInitialized);
        applicationInterface.dartsMultiAttemptScoreControllerIsInitalized.connect(dartsScoreMultiAttemptIsInitialized);
        body.requestTournaments();
    }
    Component.onDestruction: {
        body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest);
        applicationInterface.sendTournaments.disconnect(recieveTournaments);
        body.sendClickedTournamentIndex.disconnect(applicationInterface.handleSetCurrentTournamentRequest);
        applicationInterface.dartsPointMultiColumnsInitialized.disconnect(dartsPointSingleAttemptInitialized);
        applicationInterface.dartsMultiAttemptScoreControllerIsInitalized.disconnect(dartsScoreMultiAttemptIsInitialized);
    }
}
