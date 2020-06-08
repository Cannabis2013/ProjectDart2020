import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

GridLayout
{
    id: bodyLayout
    
    rows:2
    columns: 2
    Label{
        
        Layout.row: 0
        Layout.column: 0
        text: "Pick players"
        font.pointSize: 24
        
        Layout.fillWidth: true
        
        horizontalAlignment: Qt.AlignHCenter
    }
    
    MyListView {
        id: pickPlayerView
        
        itemFontSize: 10
        itemSelectedColor: "blue"
        
        Layout.row: 1
        Layout.column: 0
        
        Component.onCompleted: {
            addItem("Martin","Hansen","havnetrold2002@yahoo.dk", "232-322-111");
            addItem("Kent","Killerhertz","Killerhertz@gmail.com", "644-233-442");
        }
    }
}
