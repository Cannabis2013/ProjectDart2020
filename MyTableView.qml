import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import ApplicationInterface 1.0

Flickable
{
    clip: true
    
    contentWidth: 300
    contentHeight: 100
    
    width: 100
    height: 100
    
    CustomTable
    {
        anchors.centerIn: parent
        width: 300
        height: 100
    }
}
