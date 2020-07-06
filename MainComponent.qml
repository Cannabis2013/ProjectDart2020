import QtQuick 2.0

Item {
    id: body

    signal backPushed

    Component{
        id: gamePageComponent

        Page{
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent
            pageTitle: "Game"
            pageContent: GamePageContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
        }
    }

    Component{
        id: setupPageComponent
        Page {
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent
            pageTitle: "Setup tournament"
            pageContent: SetupPageContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
        }
    }

    Component{
        id: tournamentPageComponent
        Page{
            id: tournamentPage
            pageTitle: "Tournaments"
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
            pageContent: TournamentPageContent{
                onCreateTournamentClicked: pageLoader.sourceComponent = setupPageComponent
                onStartGameClicked: pageLoader.sourceComponent = gamePageComponent
            }
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
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
    }
    Component.onCompleted: pageLoader.sourceComponent = startPageComponent
}
