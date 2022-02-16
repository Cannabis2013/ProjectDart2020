import QtQuick 2.12
Item {
    id: body
    signal backPushed
    Component{
        id: createPlayerComponent
        Page{
            onBackButtonPressed: pageLoader.sourceComponent = managePageComponent
            pageIconUrl: "qrc:/pictures/Ressources/users.png"
            pageContent: CreatePlayerContent{}
        }
    }
    Component{
        id: managePageComponent
        Page{
            onBackButtonPressed: pageLoader.sourceComponent = startPageComponent
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
            pageContent: CreateTournamentContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
        }
    }
    Component{
        id: tournamentPageComponent
        Page{
            id: tournamentPage
            pageContent: TournamentPageContent{
                onCreateTournamentClicked: pageLoader.sourceComponent = createTournamentComponent
                onManageButtonClicked: pageLoader.sourceComponent = managePageComponent
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
            pageContent: DPCContent{}
            Component.onCompleted: body.backPushed.connect(backButtonPressed)
            onBackButtonPressed: pageLoader.sourceComponent = tournamentPageComponent
        }
    }
    Component
    {
        id: dartsScoreSingleColumn
        Page{
            pageContent: DSCContent{}
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
