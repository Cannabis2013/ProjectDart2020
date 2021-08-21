import QtQuick 2.15
import CustomItems 1.0
import DartsTableUtils 1.0

import "dpmcheaderscripts.js" as HeaderScripts
import "dpmcboardscripts.js" as ScoreScripts

ScoreBoard {
    id: dPMCBoard
    // Data related
    signal setData(string playerName, int point, int score)
    onSetData: ScoreScripts.setData(playerName,score,point)
    signal takeData(string playerName)
    onTakeData: ScoreScripts.takeData(playerName)
    onClearData: ScoreScripts.clearAll()
    // Header related
    onAppendHeaderData: HeaderScripts.addHeaderData(data,defaultVal)
    // Cell related
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)
    property int attempts : 3
    onAttemptsChanged: horizontalHeaderModel.numberOfAttempts = attempts
    readonly property QtObject dpmcTableFonts : DpmcTableFonts{}
    TableSectionMetrics{id: fontsMetric}
    DartsTableWidths
    {
        id: tableWidthProvider
        minimumColumnWidth: 64
        scale: 1.05
    }
    DartsTableHeights
    {
        id: tableHeightProvider
        minimumRowHeight: 72
        scale: 1.05
    }
    StringHeaderModel{
        id: verticalHeaderModel
        onDataChanged: ScoreScripts.refreshHeaders()
    }
    RoundHeaderLabelByAttempt{
        id: horizontalHeaderModel
        numberOfAttempts : attempts
    }
    columnWidthProvider: function(column){return tableWidthProvider.columnWidthAt(column)}
    rowHeightProvider: function(row){return tableHeightProvider.rowHeightAt(row)}
    model: DPMCTableModel {
        id: dartsDataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        minimumColumnCount: 4
    }
    cellDelegate: DPMCBoardDelegate {
        id: boardDelegate
        text: display
        onTextChanged: ScoreScripts.handleTextChanged(text,boardDelegate)
    }
}
