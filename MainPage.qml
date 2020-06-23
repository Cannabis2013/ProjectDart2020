import QtQuick 2.0

Item {
    id: body

    Component{
        id: setupPage
        SetupPage {
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPage
        }
    }

    Component{
        id: tournamentPage

        TournamentPage{
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
        }
    }

    Component
    {
        id: startPageComponent
        StartPage{
            id: startPage

            onRequestSetupGamePage: pageLoader.sourceComponent = tournamentPage
            onRequestLoginPage: {}
            onRequestLogOut: {}
            onRequestQuit: destructor()

            padding: 12

        }
    }

    Loader{
        id: pageLoader
        anchors.fill: parent
        sourceComponent: startPageComponent
    }
}
