import QtQuick 2.15
import CustomItems 1.0
import DartsTableUtils 1.0
import "dsscboardscripts.js" as ScoreScripts
ScoreBoard {
    id: scoreBoardBody
    onWidthChanged: ScoreScripts.updateScoreBoard()
    // Data related
    signal setData(string playerName, int score)
    signal takeData(int row, int column,string playerName)
    onSetData: ScoreScripts.setData(playerName,score)
    onTakeData: ScoreScripts.takeData(row,column,playerName)
    onClearData: ScoreScripts.clearTable();
    // Header related
    verticalHeaderVisible: true
    onAppendHeaderData: ScoreScripts.setHeaderData(data,defaultVal)
    // Cell related
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)
    onAppendHeader: ScoreScripts.appendHeader(data)
    QtObject
    {
        id: tableFonts
        property string headerFontFamily: "MS Sans Serif"
        property int headerFontSize: 16
        property string scoreFontFamily: "MS Sans Serif"
        property int scoreFontSize: 32
    }
    TableSectionMetrics
    {
        id: fontsMetric
    }
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
        onDataChanged: ScoreScripts.refreshVerticalHeader()
    }
    columnWidthProvider: function(column){
        return tableWidthProvider.columnWidthAt(column);
    }
    rowHeightProvider: function(row)
    {
        return tableHeightProvider.rowHeightAt(row);
    }
    model: DSSCTableModel{
        id: dataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
    }
    cellDelegate: ScoreRectDelegate {
        id: delegate
        text: display
        onTextChanged: ScoreScripts.setDelegateText(text,delegate)
        scoreFontSize: tableFonts.scoreFontSize
        cellBorderWidth: scoreBoardBody.cellBorderWidth
        cellColor: "green"
        cellBorderRadius: 10
    }
}
