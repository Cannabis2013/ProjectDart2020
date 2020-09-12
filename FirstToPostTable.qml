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

ScoreBoard{
    color: "transparent"
    verticalHeaderFillMode: 0x1
    scoreFontSize: 20
    pointFontSize: 10
}

