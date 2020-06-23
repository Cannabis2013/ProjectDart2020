import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import ApplicationInterface 1.0


ApplicationWindow {
    id: applicationWindow

    visible: true

    color: "lightgray"

    x: 1024 - width/2
    y: 1152 /2 - height/2

    minimumWidth: 400
    minimumHeight: 600

    title: qsTr("Dart2020")

    function destructor(){
        // Save state and clean up

        print("Quit requestet and handled");
        Qt.quit();
    }

    ProjectDart
    {
        id: projectDart
    }

    Item {
        id: keyListener
        anchors.fill: parent
        focus: true

        Keys.onPressed: {
            // Only relevant for desktop users
            if(event.key === Qt.Key_Q && event.modifiers & Qt.ControlModifier){
                destructor();
                event.accepted = true;
            }
        }
    }

    MainComponent{
        id: mainPage

        anchors.fill: parent
    }
}

