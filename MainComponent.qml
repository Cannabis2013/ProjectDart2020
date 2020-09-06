import QtQuick 2.12

Item {
    id: body
    signal backPushed

    Component{
        id: createPlayerComponent

        Page{
            onBackButtonPressed: pageLoader.sourceComponent = managePageComponent
            pageContent: CreatePlayerContent{
            }
        }
    }

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
        id: managePageComponent
        Page{
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
            pageTitle: "Manage tournaments and players"
            pageContent: ManagePageContent{
                onRequestCreatePlayerPage: pageLoader.sourceComponent = createPlayerComponent
                onRequestCreateTournamentPage: pageLoader.sourceComponent = createTournamentComponent
            }
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
        }
    }

    Component{
        id: createTournamentComponent
        Page {
            onBackButtonPressed: pageLoader.sourceComponent = managePageComponent
            pageTitle: "Setup tournament"
            pageContent: CreateTournamentContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
        }
    }

    Component{
        id: tournamentPageComponent
        Page{
            id: tournamentPage
            pageTitle: "Get started.."
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
            pageContent: TournamentPageContent{
                onCreateTournamentClicked: pageLoader.sourceComponent = createTournamentComponent
                onManageButtonClicked: pageLoader.sourceComponent = managePageComponent
                onStartGameClicked: pageLoader.sourceComponent = gamePageComponent
            }
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
        }
    }

    Component
    {
        id: startPageComponent
        Page{
            anchors.fill: parent
            backButtonVisible: false
            backButtonDisabled : true
            pageTitle: "Welcome"
            pageContent: StartPageContent{
                onSetupGameClicked: pageLoader.sourceComponent = tournamentPageComponent
                onManageContentClicked: pageLoader.sourceComponent = managePageComponent
                onLoginButtonClicked: {}
                onLogoutButtonClicked: {}
                onQuitButtonClicked: destructor()
            }
        }
    }
    Loader{
        id: pageLoader
        anchors.fill: parent

    }
    Component.onCompleted: pageLoader.sourceComponent = startPageComponent
}
