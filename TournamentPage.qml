import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle{
    id: body

    clip: true

    color: "transparent"

    Layout.fillHeight: true
    Layout.fillWidth: true

   GridLayout
   {
       anchors.fill: parent

       columnSpacing: 0
       rowSpacing: 9

       flow: GridLayout.TopToBottom

       ListComponent {
           id: listComponent

           Layout.fillWidth: true
           Layout.fillHeight: true

           color: "lightgray"
           radius: 15

           componentTitle: "Select tournament"
           itemTextColor: "white"
           itemSelectedtextColor: "white"
           itemSelectedBackgroundColor: "blue"

           itemHoveredColor: Qt.rgba(23,43,22,0.1)

           itemFontSize: 10

           itemWidth: 256
       }

       PushButton{
           Layout.alignment: Qt.AlignLeft

           width: 160
           height: 40
           text: "Create tournament"
       }

       Rectangle{
           height: 64
       }

       PushButton{
           Layout.alignment: Qt.AlignHCenter

           width: 128
           height: 40

           text: "Start game"
       }

   }


}
