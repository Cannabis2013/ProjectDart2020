import QtQuick 2.15
import CustomItems 1.0

import "dartspointscoreboardscripts.js" as ScoreScripts

ScoreBoard {
    id: multiColumnPointBoard
    // Data related
    signal setData(string playerName, int point, int score)
    onSetData: ScoreScripts.setData(playerName,score,point)
    signal takeData(string playerName)
    signal editData(int row, int column,int point,int score)
    onTakeData: ScoreScripts.takeData(playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)
    onClearData: ScoreScripts.clearAll()
    // Header related
    onAppendHeaderData: ScoreScripts.addHeaderData(data,defaultVal)
    // Cell related
    property color scoreCellColor: "transparent"
    onScoreCellColorChanged: cellDelegate.cellColor = multiColumnPointBoard.scoreCellColor
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    property int attempts : 3
    onAttemptsChanged: horizontalHeaderModel.numberOfAttempts = attempts

    modelScale: 1.5
    onModelScaleChanged: dartsDataModel.scale = modelScale

    StringHeaderModel{
        id: verticalHeaderModel
        onDataChanged: ScoreScripts.refreshHeaders()
    }

    RoundHeaderLabelByAttempt{
        id: horizontalHeaderModel
        numberOfAttempts : attempts
    }

    columnWidthProvider: function(column){
        return 128;
    }

    rowHeightProvider: function(row){
        return 64;
    }

    model: DartsPointMultiColumnDataModel {
        id: dartsDataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        minimumColumnCount: 4
    }
    cellDelegate: SingleAttemptCellDelegate {
        id: boardDelegate
        text: display
        cellBorderWidth: multiColumnPointBoard.cellBorderWidth
        cellColor: multiColumnPointBoard.scoreCellColor
        scoreFontSize: 14
        pointFontSize: 10
        onTextChanged: ScoreScripts.handleTextChanged(text,boardDelegate)
    }
}
