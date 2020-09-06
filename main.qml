import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

ApplicationWindow {
    id: applicationWindow

    readonly property int defaultPageContentWidth: 512

    visible: true

    color: "lightgray"

    minimumHeight: 640
    minimumWidth: 400
    width: 480
    height: 640

    Screen.orientationUpdateMask:  Qt.LandscapeOrientation | Qt.PortraitOrientation

    title: qsTr("Dart2020")

    function destructor(){
        // Save state and clean up
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

