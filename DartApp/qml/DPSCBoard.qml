import QtQuick 2.0
import CustomItems 1.0
import DartsTableUtils 1.0

import "dpcboardgeometry.js" as GeometryScripts
import "dpcboardscripts.js" as DataScripts
import "dpcBoardHeaderScripts.js" as HeaderScripts
import "dpcBoardDelegateScripts.js" as DelegateScripts

DartsScoreBoard {
    id: scoreBoardBody
    height: 128
    onWidthChanged: GeometryScripts.updateContentHeight()
    signal itemsEnabled(bool enabled)
    signal setData(string playerName, int score, int min, double mid, int max, bool inGame)
    onSetData: DataScripts.setData(playerName,score,min,mid,max,inGame)
    signal takeData(int row, int column,string playerName)
    onTakeData: DataScripts.takeData(row,column,playerName)
    onClearData:  DataScripts.clearTable()
    onAppendHeaderData: HeaderScripts.setHeaderData(data,defaultVal)
    onAppendHeader: HeaderScripts.appendHeader(data)
    onNotifyCellPosition: GeometryScripts.setViewPosition(x,y)
    readonly property DSSCBoardFonts tableFonts: DSSCBoardFonts{}

    TableSectionMetrics{id: fontsMetric}

    DartsTableWidths{
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

    PlayerDataModel{
        id: playerDataModel
    }

    columnWidthProvider: function(column){
        return tableDisplayWidth;
    }

    rowHeightProvider: function(row){
        return 64;
    }
    model: DartsPSCTableModel{
        id: dataModel
        onDataChanged: GeometryScripts.updateContentHeight()
        minimumColumnCount: 1
    }
    cellDelegate: BoardDelegateContentRect {
        id: delegate
        playerName: playerDataModel.playerName(row)
        score: DelegateScripts.updateDelegate(display,this,row)
    }
}
