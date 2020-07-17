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

    function recieveTournament(title,maxPlayersCount,numberOfThrows,gameMode,keyPoint,playersCount){
        tournamentListView.addTournamentItem(title,numberOfThrows,maxPlayersCount,keyPoint,playersCount);
    }
    onReplyFromBackendRecieved: {
        if(status === 0x7)
        {
            startButton.enabled = true;
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

           onItemSelected: sendClickedTournamentIndex(index)

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
           onClicked: startGameClicked();
       }
    }
    Component.onCompleted: {
        body.requestTournaments.connect(localDart.requestTournaments); // Request initial tournaments
        localDart.sendRequestetTournament.connect(recieveTournament)
        body.sendClickedTournamentIndex.connect(localDart.setCurrentActiveTournament)
        requestUpdate();
    }
    Component.onDestruction: {
        localDart.sendRequestetTournament.disconnect(recieveTournament);
        body.sendClickedTournamentIndex.disconnect(localDart.setCurrentActiveTournament)
        body.requestTournaments.disconnect(localDart.requestTournaments);
    }
}
