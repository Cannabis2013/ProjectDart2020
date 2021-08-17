import QtQuick 2.15
import CustomItems 1.0
import DartsTableUtils 1.0

import "dartspmcheaderscripts.js" as HeaderScripts
import "dartspmcboardscripts.js" as ScoreScripts

ScoreBoard {
    id: pmcBoard
    // Data related
    signal setData(string playerName, int point, int score)
    onSetData: ScoreScripts.setData(playerName,score,point)
    signal takeData(string playerName)
    signal editData(int row, int column,int point,int score)
    onTakeData: ScoreScripts.takeData(playerName)
    onClearData: ScoreScripts.clearAll()
    // Header related
    onAppendHeaderData: HeaderScripts.addHeaderData(data,defaultVal)
    // Cell related
    property color scoreCellColor: "transparent"
    onScoreCellColorChanged: cellDelegate.cellColor = pmcBoard.scoreCellColor
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    property int attempts : 3
    onAttemptsChanged: horizontalHeaderModel.numberOfAttempts = attempts

    modelScale: 1.5
    onModelScaleChanged: dartsDataModel.scale = modelScale

    QtObject
    {
        id: tableFonts
        property string headerFontFamily: "MS Sans Serif"
        property int headerFontSize: 16
        property string scoreFontFamily: "MS Sans Serif"
        property int scoreFontSize: 14
        property string pointFontFamily: "MS Sans Serif"
        property int pointFontSize: 10
    }
    TableSectionMetrics
    {
        id: fontsMetric
        scale: 1.05
    }
    DartsTableWidths
    {
        id: tableColumnWidths
    }
    DartsTableHeights
    {
        id: tableHeightProvider
        minimumRowHeight: 72
    }

    StringHeaderModel{
        id: verticalHeaderModel
        onDataChanged: ScoreScripts.refreshHeaders()
    }
    RoundHeaderLabelByAttempt{
        id: horizontalHeaderModel
        numberOfAttempts : attempts
    }
    columnWidthProvider: function(column){return ScoreScripts.columnWidthAt(column)}
    rowHeightProvider: function(row){return ScoreScripts.rowHeightAt(row)}
    model: DartsPMCTableModel {
        id: dartsDataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        minimumColumnCount: 4
    }
    cellDelegate: SingleAttemptCellDelegate {
        id: boardDelegate
        text: display
        cellBorderWidth: pmcBoard.cellBorderWidth
        cellColor: pmcBoard.scoreCellColor
        scoreFontSize: 14
        pointFontSize: 10
        onTextChanged: ScoreScripts.handleTextChanged(text,boardDelegate)
    }
}
