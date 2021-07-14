import QtQuick 2.4
import QtQuick.Layouts 1.3

import "tournamentPageScripts.js" as Scripts

Content{
    id: body
    clip: true
    signal createTournamentClicked
    signal dartsPointSingleColumnInitialized
    signal dartsPointMultiColumnInitialized
    signal dartsScoreSingleColumnInitialized
    signal manageButtonClicked
    signal requestTournaments
    signal requestDeleteTournaments(var indexes)
    signal sendClickedTournamentIndex(int index)
    QtObject{
        id: currentValues
        property int currentIndex: -1
    }
    onRequestUpdate: requestTournaments()
    GridLayout
    {
       anchors.fill: parent
       columnSpacing: 0
       rowSpacing: 4
       flow: GridLayout.TopToBottom
       TournamentPageListView {
           id: tournamentListView
           Layout.fillHeight: true
           Layout.fillWidth: true
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
    Component.onCompleted: Scripts.initialize()
    Component.onDestruction: Scripts.disconnect()
}
