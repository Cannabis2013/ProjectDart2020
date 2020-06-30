import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle{

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
           id: listComponent

           Layout.fillWidth: true
           Layout.fillHeight: true

           color: "white"
           radius: 15

           componentTitle: "Select tournament"
           itemTextColor: "white"
           itemSelectedtextColor: "white"
           itemSelectedBackgroundColor: "silver"

           itemHoveredColor: Qt.rgba(23,43,22,0.1)

           itemFontSize: 10

           itemWidth: 256
       }
       GridLayout{
           flow: GridLayout.LeftToRight

           columnSpacing: 2

           Rectangle{
               Layout.fillWidth: true
           }

           PushButton{

               width: 64
               height: 30
               text: "Create"
               fontSize: 8

               textColor: "white"
               backgroundColor: "green"

               buttonRadius: 5

               onClicked: createTournamentClicked()
           }

           PushButton{
               Layout.alignment: Qt.AlignLeft

               width: 64
               height: 30
               text: "Delete"
               fontSize: 8

               textColor: "white"
               backgroundColor: "green"

               buttonRadius: 5
           }
       }


       Rectangle{
           height: 64
       }

       PushButton{
           Layout.alignment: Qt.AlignHCenter

           width: 128
           height: 40

           textColor: "white"
           backgroundColor: "green"

           text: "Start game"

           onClicked: startGameClicked()
       }

    }
}
