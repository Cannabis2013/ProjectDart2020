import QtQuick 2.0
import CustomItems 1.0
import DartsTableUtils 1.0
import "dpscboardscripts.js" as ScoreBoardScripts
ScoreBoard {
    id: scoreBoardBody
    onWidthChanged: ScoreBoardScripts.updateScoreBoard()
    // Data related
    signal setData(string playerName, int point, int score)
    onSetData: ScoreBoardScripts.setData(playerName,point,score)
    signal takeData(int row, int column,string playerName)
    // Manipulate state such as: add score, takescore, edit score
    onTakeData: ScoreBoardScripts.takeData(row,column,playerName)
    onClearData:  ScoreBoardScripts.clearTable()
    // Header related
    onAppendHeaderData: ScoreBoardScripts.setHeaderData(data,defaultVal)
    onAppendHeader: ScoreBoardScripts.appendHeader(data)
    // Cell related
    onNotifyCellPosition: ScoreBoardScripts.setViewPosition(x,y)
    readonly property DSSCBoardFonts tableFonts: DSSCBoardFonts{}
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
        onDataChanged: ScoreBoardScripts.refreshVerticalHeader()
    }
    columnWidthProvider: function(column){
        return tableWidthProvider.columnWidthAt(column);
    }
    rowHeightProvider: function(row)
    {
        return tableHeightProvider.rowHeightAt(row);
    }
    model: DartsPSCTableModel{
        id: dataModel
        onDataChanged: ScoreBoardScripts.updateScoreBoard();
        minimumColumnCount: 1
    }
    cellDelegate: DPSCBoardDelegate {
        id: delegate
        scoreFontSize: tableFonts.scoreFontSize
        text: display
        onTextChanged: ScoreBoardScripts.setDelegateText(text,delegate)
    }
}
