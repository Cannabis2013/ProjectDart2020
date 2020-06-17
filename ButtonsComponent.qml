import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Rectangle{
    
    signal startTournamentClicked
    signal startLaterClicked

    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
    
    GridLayout{
        rows: 1
        columns: 3
        
        anchors.fill: parent
        
        rowSpacing: 5
        
        PushButton{
            text: "Start later"
            
            Layout.row: 0
            Layout.column: 0
            
            fontSize: 8
            textColor: "white"
            
            height: 30
            width: 80

            onClicked: startLaterClicked()
        }
        
        PushButton{
            text: "Start tournament"
            
            Layout.row: 0
            Layout.column: 1
            
            fontSize: 8
            textColor: "white"
            
            height: 30
            width: 100

            onClicked: startTournamentClicked()
        }
    }
}
