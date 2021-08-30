import QtQuick 2.15
import CustomItems 1.0
import DartsTableUtils 1.0
import "dsscboardscripts.js" as ScoreScripts
ScoreBoard {
    id: scoreBoardBody
    onWidthChanged: ScoreScripts.updateScoreBoard()
    signal setData(string playerName, int score)
    signal takeData(int row, int column,string playerName)
    onSetData: ScoreScripts.setData(playerName,score)
    onTakeData: ScoreScripts.takeData(row,column,playerName)
    onClearData: ScoreScripts.clearTable()
    onAppendHeaderData: ScoreScripts.setHeaderData(data,defaultVal)
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)
    onAppendHeader: ScoreScripts.appendHeader(data)
    readonly property DSSCTableFonts tableFonts: DSSCTableFonts{}
    readonly property TableSectionMetrics fontsMetric: TableSectionMetrics{}
    DartsTableWidths{id: tableWidthProvider}
    DartsTableHeights{id: tableHeightProvider}
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
    cellDelegate: DSSCDelegate {
        id: delegate
        scoreFontSize: tableFonts.scoreFontSize
        onTextChanged: ScoreScripts.setDelegateText(text,delegate)
    }
}
