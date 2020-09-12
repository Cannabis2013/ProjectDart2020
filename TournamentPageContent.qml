import QtQuick 2.4
import QtQuick.Layouts 1.3

import "tournamentPageScripts.js" as TournamentPageScripts

Content{

    id: body
    clip: true

    signal createTournamentClicked
    signal startGameClicked
    signal manageButtonClicked
    signal requestTournaments
    signal requestDeleteTournaments(var indexes)
    signal sendClickedTournamentIndex(int index)

    QtObject{
        id: currentValues

        property int currentIndex: -1
    }

    function recieveTournament(title,numberOfThrows,gameMode,keyPoint,playersCount){
        tournamentListView.addItemModel({"type" : "tournament",
                                            "tournamentTitle" : title,
                                            "Throws" : numberOfThrows,
                                            "KeyPoint" : keyPoint,
                                            "playersCount" : playersCount})
    }
    onReplyFromBackendRecieved: {
        if(response === 0x45) // Backend has responded with a status code that signals it is initialized and ready to start
        {
            startGameClicked();
        }
        else if(response == 0x29) // Backend has responded with a status code that signals it has succesfully updated its state
        {
            tournamentListView.unSelectAllItems();
            tournamentListView.removeItemModels(args);
        }
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
        applicationInterface.sendRequestedTournament.connect(recieveTournament);
        body.sendClickedTournamentIndex.connect(applicationInterface.handleSetCurrentTournamentRequest);
        body.requestTournaments();
    }
    Component.onDestruction: {
        body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest);
        applicationInterface.sendRequestedTournament.disconnect(recieveTournament);
        body.sendClickedTournamentIndex.disconnect(applicationInterface.handleSetCurrentTournamentRequest);
        }
}
