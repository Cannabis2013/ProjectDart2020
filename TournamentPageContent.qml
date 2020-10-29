import QtQuick 2.4
import QtQuick.Layouts 1.3

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
        /*
          Backend has responded with a status code that signals it is initialized and ready to start
          */
        if(response === 0x45)
        {
            startGameClicked();
        }
        /*
          Backend responds that there is detected an inconsistency
          between the currently selected tournament
          and its assigned player models.
          */
        else if(response === 0x39)
        {
            /*
              TODO:
                - Notify the player about the issue
                - Maybe provide some options to the player to correct the issue
              */
            print("Inconsistencies detected");
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
           itemTitleTextColor: ThemeContext.tournamentListViewTextColor
           itemDescriptionFontColor: ThemeContext.tournamentListViewTextColor
           labelTextColor: ThemeContext.tournamentListViewTextColor
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
