import QtQuick 2.0

Item {
    id: body

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
            onRequestQuit: destructor()


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
