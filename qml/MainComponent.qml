import QtQuick 2.12

Item {
        id: body

        signal backPushed

        Component {
                id: createPlayerComponent
                CreatePlayerContent {
                        onBackButtonClicked: pageLoader.sourceComponent = managePageComponent
                }
        }

        Component {
                id: managePageComponent
                ManagePageContent {
                        onBackButtonClicked: pageLoader.sourceComponent = startPageComponent
                        onRequestCreatePlayerPage: pageLoader.sourceComponent
                                                   = createPlayerComponent
                        onRequestCreateTournamentPage: pageLoader.sourceComponent
                                                       = createTournamentComponent
                        Component.onCompleted: body.backPushed.connect(
                                                       backButtonClicked)
                }
        }

        Component {
                id: createTournamentComponent
                CreateTournamentContent {
                        onBackButtonClicked: pageLoader.sourceComponent = managePageComponent
                        Component.onCompleted: body.backPushed.connect(
                                                       backButtonClicked)
                }
        }

        Component {
                id: tournamentPageComponent
                TournamentPageContent {
                        onCreateTournamentClicked: pageLoader.sourceComponent
                                                   = createTournamentComponent
                        onManageButtonClicked: pageLoader.sourceComponent = managePageComponent
                        onDartsScoreSingleColumnInitialized: pageLoader.sourceComponent
                                                             = dartsScoreSingleColumn
                        onDartsPointSingleColumnInitialized: pageLoader.sourceComponent
                                                             = dartsPointSingleColumn
                        onBackButtonClicked: pageLoader.sourceComponent = startPageComponent
                        Component.onCompleted: body.backPushed.connect(
                                                       backButtonClicked)
                }
        }

        Component {
                id: startPageComponent
                StartPageContent {
                        onSetupGameClicked: pageLoader.sourceComponent = tournamentPageComponent
                        onManageContentClicked: pageLoader.sourceComponent = managePageComponent
                }
        }

        Component {
                id: dartsPointSingleColumn
                DPCContent {
                        Component.onCompleted: body.backPushed.connect(
                                                       backButtonPressed)
                        onBackButtonClicked: pageLoader.sourceComponent = tournamentPageComponent
                }
        }

        Component {
                id: dartsScoreSingleColumn
                DSCContent {
                        Component.onCompleted: body.backPushed.connect(
                                                       backButtonPressed)
                        onBackButtonClicked: pageLoader.sourceComponent = tournamentPageComponent
                }
        }

        Loader {
                id: pageLoader
                anchors.fill: parent
                sourceComponent: startPageComponent
        }
}
