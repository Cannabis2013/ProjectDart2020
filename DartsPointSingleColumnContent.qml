import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dartspointsinglecolumnscripts.js" as PointSingleColumnScripts
import "pointsinglecolumnstatescripts.js" as PointStateScripts

Content {
    id: dartsPointSingleColumnBody
    signal requestControllerValues
    signal requestMultiAttemptScores
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    onRequestRestart: PointSingleColumnScripts.handleRequestTournamentReset()
    signal requestUndo
    signal requestRedo
    signal sendInput(string json)
    signal setupGame
    signal requestPersistState
    /*
      Tournament metadata property
      */
    QtObject{
        id: dartsPointSingleColumnMetaValues
        property string title: ""
        property int keyPoint: 501
        property int attempts: 3
        property string winnerName: ""
        property var assignedPlayerNames: []
    }

    GridLayout{
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        TurnController{
            id: pointSingleColumnTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
            onStartButtonClicked: requestStart()
            onResumeButtonClicked: requestStart()
            onPauseButtonClicked: requestStop()
            onRestartButtonClicked: requestRestart()
            onLeftButtonClicked: PointSingleColumnScripts.undoClicked()
            onRightButtonClicked: PointSingleColumnScripts.redoClicked()
        }
        DartsPointSingleColumnBoard{
            id: singleColumnPointBoard
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 160
        }
        MyRectangle{
            Layout.fillHeight: true
        }

        KeyDataDisplay{
            id: keyDataDisplay
            Layout.fillWidth: true
            Layout.maximumHeight: 40
        }
        Rectangle{
             color: "transparent"
             height: 5
        }
        PointKeyPad{
            id: pointKeyPad
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: 384
            Layout.minimumHeight: 128
        }
    }
    states: [
        State {
            name: "winner"
            StateChangeScript{
                script: PointStateScripts.declareWinner()
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: PointStateScripts.backendIsStopped()
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: pointSingleColumnTurnController.backendIsReady()
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: PointStateScripts.backendProcessesInput()
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: PointStateScripts.backendAwaitsInput()
            }
        }
    ]
    Component.onCompleted: PointSingleColumnScripts.initializeComponent()
    Component.onDestruction: PointSingleColumnScripts.disconnectInterface()
}
