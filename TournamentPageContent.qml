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

    function recieveTournament(title,maxPlayersCount,numberOfThrows,gameMode,keyPoint,playersCount){
        tournamentListView.addTournamentItem(title,numberOfThrows,maxPlayersCount,keyPoint,playersCount);
    }
    onReplyFromBackendRecieved: {
        if(status === 0x10)
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
           itemSelectedtextColor: "black"
           itemSelectedBackgroundColor: "silver"

           itemHoveredColor: "darkgray"

           onItemSelected: {
               startButton.enabled = true
               currentValues.currentIndex = index;
           }

           itemFontSize: 10

           itemWidth: 256

           allowCheckState: true
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
       Rectangle{
           height: 64
       }

       PushButton{
           id: startButton
           Layout.alignment: Qt.AlignHCenter
           width: 128
           height: 40
           fontSize: 16
           textColor: "white"
           backgroundColor: "green"
           text: "Start game"
           enabled: false
           onClicked: sendClickedTournamentIndex(currentValues.currentIndex);
       }
    }
    Component.onCompleted: {
        body.requestTournaments.connect(localDart.handleTournamentsRequest); // Request initial tournaments
        localDart.sendRequestedTournament.connect(recieveTournament)
        body.sendClickedTournamentIndex.connect(localDart.handleSetCurrentTournamentRequest)
        body.requestTournaments();
    }
    Component.onDestruction: {
        body.requestTournaments.disconnect(localDart.handleTournamentsRequest);
        localDart.sendRequestedTournament.disconnect(recieveTournament)
        body.sendClickedTournamentIndex.disconnect(localDart.handleSetCurrentTournamentRequest)
    }
}
