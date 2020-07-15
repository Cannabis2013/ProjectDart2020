import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: applicationWindow

    readonly property int defaultPageContentWidth: 512

    visible: true

    color: "lightgray"

    width: 480
    height: 640

    title: qsTr("Dart2020")

    function destructor(){
        // Save state and clean up

        print("Quit requestet and handled");
        Qt.quit();
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
            else if(event.key === Qt.Key_Back)
            {
                mainPage.backPushed();
                event.accepted = true;
            }
        }
    }

    MainComponent{
        id: mainPage

        anchors.fill: parent
    }
}

