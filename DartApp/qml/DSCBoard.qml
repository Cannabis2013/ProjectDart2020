import QtQuick 2.15
import CustomItems 1.0
import DartsTableUtils 1.0
import "dsscboardscripts.js" as ScoreScripts
DartsScoreBoard {
    id: scoreBoardBody
    height: 128
    onWidthChanged: ScoreScripts.updateScoreBoard()
    signal setData(string playerName,int score,int min,double mid,int max)
    signal takeData(int row, int column,string playerName)
    onSetData: ScoreScripts.setData(playerName,score,min,mid,max)
    onTakeData: ScoreScripts.takeData(row,column,playerName)
    onClearData: ScoreScripts.clearTable()
    onAppendHeaderData: ScoreScripts.setHeaderData(data,defaultVal)
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)
    onAppendHeader: ScoreScripts.appendHeader(data)
    readonly property DSSCTableFonts tableFonts: DSSCTableFonts{}
    readonly property TableSectionMetrics fontsMetric: TableSectionMetrics{}
    DartsTableWidths{
        id: tableWidthProvider
        scale: 1.25
    }
    DartsTableHeights{
        id: tableHeightProvider
    }
    PlayerDataModel{
        id: playerDataModel
    }
    columnWidthProvider: function(column){
        return tableDisplayWidth;
    }
    rowHeightProvider: function(row)
    {
        return 64;
    }
    model: DSCTableModel{
        id: dataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
    }
    cellDelegate: BoardDelegateContentRect {
        id: tableDelegate
        itemEnabled: true
        playerName: playerDataModel.playerName(row)
        score: ScoreScripts.updateDelegate(display,this,row);
    }
}
