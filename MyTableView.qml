import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import ApplicationInterface 1.0

Item
{
    id: myTableViewBody
    clip: true

    function appendHeader(data, orientation){
        myCustomTable.appendHeader(data,orientation);
    }

    function setData(data,row,column)
    {
        myCustomTable.addData(row,column, data);
    }
    
    CustomTable
    {
        id: myCustomTable

        anchors.centerIn: parent
        width: 300
        height: 50

    }
}
