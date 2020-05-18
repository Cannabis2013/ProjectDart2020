import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    color: "lightgray"
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar
    {

        Menu
        {
            title : qsTr("File")
        }
    }


}
