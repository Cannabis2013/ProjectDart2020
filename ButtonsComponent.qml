import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle{
    
    signal startClicked
    signal saveClicked

    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
    
    GridLayout{
        rows: 1
        columns: 3
        
        anchors.fill: parent
        
        rowSpacing: 5
        
        PushButton{
            text: "Save"
            
            Layout.row: 0
            Layout.column: 0
            
            fontSize: 8
            textColor: "white"
            backgroundColor: "green"
            
            height: 30
            width: 80

            onClicked: saveClicked()
        }
        
        PushButton{
            text: "Save and start"
            
            Layout.row: 0
            Layout.column: 1
            
            fontSize: 8
            textColor: "white"
            backgroundColor: "green"
            
            height: 30
            width: 100

            onClicked: startClicked()
        }
    }
}
