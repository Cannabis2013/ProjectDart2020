import QtQuick 2.0

Item {
    id: body

    Component{
        id: setupPage
        Page {
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent

            pageTitle: "Setup tournament"

            content: SetupPageContent{}
        }
    }

    Component{
        id: tournamentPageComponent
        Page{
            pageTitle: "Tournaments"

            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
            content: TournamentPage{}
        }

    }

    Component
    {
        id: startPageComponent
        StartPage{
            onRequestSetupGamePage: pageLoader.sourceComponent = tournamentPageComponent
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
