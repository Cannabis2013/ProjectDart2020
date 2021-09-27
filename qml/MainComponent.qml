import QtQuick 2.12

Item {
    id: body
    signal backPushed
    Component{
        id: createPlayerComponent
        Page{
            onBackButtonPressed: pageLoader.sourceComponent = managePageComponent
            pageTitle: "Create player"
            pageIconUrl: "qrc:/pictures/Ressources/users.png"
            pageContent: CreatePlayerContent{}
        }
    }
    Component{
        id: managePageComponent
        Page{
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
            pageTitle: "Manage"
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
            pageTitle: "Create tournament"
            pageContent: CreateTournamentContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
        }
    }
    Component{
        id: tournamentPageComponent
        Page{
            id: tournamentPage
            pageTitle: "Get started.."
            pageContent: TournamentPageContent{
                onCreateTournamentClicked: pageLoader.sourceComponent = createTournamentComponent
                onManageButtonClicked: pageLoader.sourceComponent = managePageComponent
                onDartsPointMultiColumnInitialized: pageLoader.sourceComponent = dartsPointMultiColumn
                onDartsScoreSingleColumnInitialized: pageLoader.sourceComponent = dartsScoreSingleColumn
                onDartsPointSingleColumnInitialized: pageLoader.sourceComponent = dartsPointSingleColumn
            }
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
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

    Component
    {
        id: dartsPointSingleColumn
        Page{
            pageTitle: "Darts multi attempt"
            pageContent: DPSCContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent
        }
    }

    Component
    {
        id: dartsPointMultiColumn
        Page{
            pageTitle : "Darts single attempt"
            pageContent: DPMCContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent
        }
    }
    Component
    {
        id: dartsScoreSingleColumn
        Page{
            pageTitle: "Darts multi attempt"
            pageContent: DSSCContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent
        }
    }

    Loader{
        id: pageLoader
        anchors.fill: parent

    }
    Component.onCompleted: pageLoader.sourceComponent = startPageComponent
}