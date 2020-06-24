import QtQuick 2.0

Item {
    id: body

    Component{
        id: gamePageComponent

        Page{
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent

            pageContent: GamePageContent{}
        }
    }

    Component{
        id: setupPageComponent
        Page {
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent

            pageTitle: "Setup tournament"

            pageContent: SetupPageContent{}
        }
    }

    Component{
        id: tournamentPageComponent
        Page{
            pageTitle: "Tournaments"

            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
            pageContent: TournamentPage{
                onCreateTournamentClicked: pageLoader.sourceComponent = setupPageComponent
                onStartGameClicked: pageLoader.sourceComponent = gamePageComponent
            }
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
