import QtQuick 2.12
import "./tournaments/createPage"
import "./players/createPlayerPage"
import "./pages/tournamentPage"
import "./pages/tournamentsPage"
import "./pages/startPage"

Item {
        id: body

        signal backPushed

        Component {
                id: createPlayerComponent
                CreatePlayerPage {
                        onBackButtonClicked: pageLoader.sourceComponent = managePageComponent
                }
        }

        Component {
                id: managePageComponent
                ManagePageContent {
                        onBackButtonClicked: pageLoader.sourceComponent = startPageComponent
                        onRequestCreatePlayerPage: pageLoader.sourceComponent = createPlayerComponent
                        onRequestCreateTournamentPage: pageLoader.sourceComponent = createTournamentComponent
                        Component.onCompleted: body.backPushed.connect(backButtonClicked)
                }
        }

        Component {
                id: createTournamentComponent
                CreateTournamentPage {
                        onBackButtonClicked: pageLoader.sourceComponent = managePageComponent
                        Component.onCompleted: body.backPushed.connect(backButtonClicked)
                }
        }

        Component {
                id: tournamentPageComponent
                TournamentsPage {
                        onCreateTournamentClicked: pageLoader.sourceComponent = createTournamentComponent
                        onManageButtonClicked: pageLoader.sourceComponent = managePageComponent
                        onDartsScoreSingleColumnInitialized: pageLoader.sourceComponent = dartsScoreSingleColumn
                        onDartsPointSingleColumnInitialized: pageLoader.sourceComponent = dartsPointSingleColumn
                        onBackButtonClicked: pageLoader.sourceComponent = startPageComponent
                        Component.onCompleted: body.backPushed.connect(backButtonClicked)
                }
        }

        Component {
                id: startPageComponent
                StartPage {
                        onSetupGameClicked: pageLoader.sourceComponent = tournamentPageComponent
                        onManageContentClicked: pageLoader.sourceComponent = managePageComponent
                }
        }

        Component {
                id: dartsPointSingleColumn
                TournamentPage {
                        Component.onCompleted: body.backPushed.connect(backButtonPressed)
                        onBackButtonClicked: pageLoader.sourceComponent = tournamentPageComponent
                }
        }

        Loader {
                id: pageLoader
                anchors.fill: parent
                sourceComponent: startPageComponent
        }
}
