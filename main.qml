import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import ApplicationInterface 1.0

ApplicationWindow {
    id: applicationWindow

    visible: true

    color: "lightgray"

    x: 120
    y: 120

    minimumWidth: 400
    minimumHeight: 500


    title: qsTr("Dart2020")

    function handleQuitRequest(){
        // Save state and clean up

        print("Quit requestet and handled");
        Qt.quit();
    }

    Item {
        id: keyListener
        anchors.fill: parent
        focus: true

        Keys.onPressed: {
            if(event.key === Qt.Key_F){
                print("Techno Tonny");
                event.accepted = true
            }
        }
    }

    Component{
        id: setupPage
        SetupPage {

            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
        }

    }

    Component
    {
        id: startPageComponent
        StartPage{
            id: startPage

            onRequestSetupGamePage: pageLoader.sourceComponent = setupPage
            onRequestLoginPage: {}
            onRequestLogOut: {}
            onRequestQuit: handleQuitRequest()

            labelColor: "#A54141"
            backgroundContentColor: "#A54141"

            padding: 12

        }
    }

    Loader{
        id: pageLoader
        anchors.fill: parent
        sourceComponent: startPageComponent
    }

}

