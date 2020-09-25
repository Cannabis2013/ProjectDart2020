import QtQuick 2.0
import QtQuick.Layouts 1.3


/*
  Controller status table:
    -> GameControllerIdle = 0x9
    -> GamecontrollerBusy = 0xa
    -> GameControllerStopped = 0xb
    -> GameControllerAwaitsInput = 0xc
    -> GameControllerRunning = 0xd
    -> GameControllerWinnerDeclared = 0xe
    -> GameControllerNotInitialized = 0xf
  */

TurnControllerItem{
    id: turnNavigator
    startButtonEnabled: false
    startButtonEnablePressAndHold: true

    onLeftButtonClicked: {
        body.state = "waitingForInputConfirmation";
        requestUndo();
    }
    
    onRightButtonClicked: {
        body.state = "waitingForInputConfirmation";
        requestRedo();
    }
}