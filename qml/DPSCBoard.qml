import QtQuick 2.0
import CustomItems 1.0
import DartsTableUtils 1.0
import "dpscboardscripts.js" as ScoreBoardScripts
DPSCScoreBoard {
    id: scoreBoardBody
    height: 128
    onWidthChanged: ScoreBoardScripts.updateScoreBoard()
    signal setData(string playerName, int point, int score)
    onSetData: ScoreBoardScripts.setData(playerName,point,score)
    signal takeData(int row, int column,string playerName)
    onTakeData: ScoreBoardScripts.takeData(row,column,playerName)
    onClearData:  ScoreBoardScripts.clearTable()
    onAppendHeaderData: ScoreBoardScripts.setHeaderData(data,defaultVal)
    onAppendHeader: ScoreBoardScripts.appendHeader(data)
    onNotifyCellPosition: ScoreBoardScripts.setViewPosition(x,y)
    readonly property DSSCBoardFonts tableFonts: DSSCBoardFonts{}
    TableSectionMetrics{id: fontsMetric}
    DartsTableWidths
    {
        id: tableWidthProvider
        minimumColumnWidth: 64
        scale: 1.25
    }
    DartsTableHeights
    {
        id: tableHeightProvider
        minimumRowHeight: 72
        scale: 1.05
    }
    StringHeaderModel{
        id: verticalHeaderModel
    }
    columnWidthProvider: function(column){
        return tableDisplayWidth;
    }
    rowHeightProvider: function(row)
    {
        return 64;
    }
    model: DartsPSCTableModel{
        id: dataModel
        onDataChanged: ScoreBoardScripts.updateScoreBoard();
        minimumColumnCount: 1
    }
    cellDelegate: BoardDelegateContentRect {
        id: delegate
        playerName: verticalHeaderModel.item(index)
        score: display
    }
}
