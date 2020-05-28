import QtQuick 2.0
import QtQuick.Layouts 1.3


Rectangle
{
    id: body
    
    GridLayout {
        id: gridLayout



        anchors.fill: parent
        rowSpacing: 2
        
        columns: 3
        
        Rectangle
        {
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 3
            Layout.fillHeight: true
            Layout.maximumHeight: 9
        }
        
        Rectangle
        {
            Layout.row: 2
            Layout.column: 1
            Layout.fillHeight: true
            Layout.maximumHeight: 64
        }
        
        PushButton
        {
            Layout.row: 3
            Layout.column: 1
            
            Layout.alignment: Qt.AlignHCenter
            text: "Start game"
        }
        
        PushButton
        {
            Layout.row: 4
            Layout.column: 1
            
            Layout.alignment: Qt.AlignHCenter
            text: "Settings"
        }

        PushButton
        {
            Layout.row: 5
            Layout.column: 1

            Layout.alignment: Qt.AlignHCenter
            text: "Quit"

            onClicked: Qt.quit()
        }
        
        Rectangle
        {
            Layout.row: 6
            Layout.column: 1
            
            Layout.fillHeight: true

            border.width: 1

        }

    }
    LoginComponent {

        width: 132

        height: 54

        clip: true

        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
