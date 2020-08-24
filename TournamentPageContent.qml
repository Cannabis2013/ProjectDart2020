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

       ListComponent {
           id: tournamentListView
           Layout.fillWidth: true
           Layout.fillHeight: true
           color: "white"
           radius: 15
           componentTitle: "Select tournament"
           itemTextColor: "black"
           itemSelectedBackgroundColor: "silver"
           itemSelectedtextColor: "black"
           itemHoveredColor: "darkgray"
           itemBackgroundColor: "lightblue"
           onItemClicked: sendClickedTournamentIndex(index)
           itemTitleFontSize: 20
           itemDescriptionFontSize: 12
           itemWidth: tournamentListView.width *0.95
           itemHeight: 64
           allowCheckState: true

           itemDecorator: "qrc:/pictures/Ressources/darttournamentmod.png"
       }
       GridLayout{
           flow: GridLayout.LeftToRight
           columnSpacing: 2
           Rectangle{
               Layout.fillWidth: true
           }

           CRUDButton{
               id: createButton
               text: "Create"
               onClicked: createTournamentClicked()
           }
           CRUDButton{
               id: deleteButton
               text: "Delete"
               onClicked: {
                   var indexes = tournamentListView.currentIndexes();
                   requestDeleteTournaments(indexes);
               }
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
        body.requestDeleteTournaments.connect(applicationInterface.handleDeleteTournamentsRequest);
        body.requestTournaments();
    }
    Component.onDestruction: {
        body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest);
        applicationInterface.sendRequestedTournament.disconnect(recieveTournament);
        body.sendClickedTournamentIndex.disconnect(applicationInterface.handleSetCurrentTournamentRequest);
        body.requestDeleteTournaments.disconnect(applicationInterface.handleDeleteTournamentsRequest);
    }
}
