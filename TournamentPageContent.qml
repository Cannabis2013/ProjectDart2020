import QtQuick 2.4
import QtQuick.Layouts 1.3

import "tournamentPageScripts.js" as TournamentPageScripts

Content{

    id: body

    clip: true

    color: "transparent"

    Layout.fillHeight: true
    Layout.fillWidth: true

    Layout.maximumWidth: defaultPageContentWidth

    Layout.alignment: Qt.AlignHCenter

    signal createTournamentClicked;
    signal startGameClicked;

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
           Layout.alignment: Qt.AlignHCenter

           width: 128
           height: 40

           fontSize: 16

           textColor: "white"
           backgroundColor: "green"

           text: "Start game"

           onClicked: TournamentPageScripts.startGame()
       }
    }
    Component.onCompleted: {
        TournamentPageScripts.updateInterface();
    }
}
