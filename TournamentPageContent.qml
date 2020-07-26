import QtQuick 2.4
import QtQuick.Layouts 1.3

import "tournamentPageScripts.js" as TournamentPageScripts

Content{

    id: body
    clip: true

    signal createTournamentClicked;
    signal startGameClicked;
    signal requestTournaments;
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
        if(status === 0x17)
        {
            startGameClicked();
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
           allowCheckState: false

           itemDecorator: "qrc:/pictures/Ressources/darttournamentmod.png"
       }
       GridLayout{
           flow: GridLayout.LeftToRight
           columnSpacing: 2
           Rectangle{
               Layout.fillWidth: true
           }

           CRUDButton{
               text: "Create"
               onClicked: createTournamentClicked()
           }
           CRUDButton{
               text: "Delete"
           }
       }
    }
    Component.onCompleted: {
        body.requestTournaments.connect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
        applicationInterface.sendRequestedTournament.connect(recieveTournament)
        body.sendClickedTournamentIndex.connect(applicationInterface.handleSetCurrentTournamentRequest)
        body.requestTournaments();
    }
    Component.onDestruction: {
        body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest);
        applicationInterface.sendRequestedTournament.disconnect(recieveTournament)
        body.sendClickedTournamentIndex.disconnect(applicationInterface.handleSetCurrentTournamentRequest)
    }
}
