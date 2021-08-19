import QtQuick 2.0
import CustomItems 1.0
import DartsTableUtils 1.0

import "dpscboardscripts.js" as DPSCBoardScripts

ScoreBoard {
    id: scoreBoardBody
    onWidthChanged: DPSCBoardScripts.updateScoreBoard()
    // Fonts
    QtObject{
        id: dataValues
        readonly property int scoreFontSize: 32
        readonly property int pointFontSize : 16
        readonly property double sizeScale: 1.2
        readonly property color delegateBackgroundColor: "green"
        readonly property int delegateBorderRadius: 10
        readonly property int headerFontSize: 16
    }
    // Data related
    signal setData(string playerName, int point, int score)
    onSetData: DPSCBoardScripts.setData(playerName,point,score)
    signal takeData(int row, int column,string playerName)
    // Manipulate state such as: add score, takescore, edit score
    onTakeData: DPSCBoardScripts.takeData(row,column,playerName)
    onClearData:  DPSCBoardScripts.clearTable()
    // Header related
    verticalHeaderVisible: true
    onAppendHeaderData: DPSCBoardScripts.setHeaderData(data,defaultVal)
    // Cell related
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: DPSCBoardScripts.setViewPosition(x,y)
    onAppendHeader: DPSCBoardScripts.appendHeader(data)

    QtObject
    {
        id: tableFonts
        property string headerFontFamily: "MS Sans Serif"
        property int headerFontSize: 16
        property string scoreFontFamily: "MS Sans Serif"
        property int scoreFontSize: 32
        property string pointFontFamily: "MS Sans Serif"
        property int pointFontSize: 16
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
        onDataChanged: DPSCBoardScripts.refreshVerticalHeader()
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
        onDataChanged: DPSCBoardScripts.updateScoreBoard();
        minimumColumnCount: 1
    }
    cellDelegate: PointDelegate {
        id: delegate
        cellBorderWidth: scoreBoardBody.cellBorderWidth
        cellColor: "green"
        pointFontSize: dataValues.pointFontSize
        radius: dataValues.delegateBorderRadius
        scoreFontSize: dataValues.scoreFontSize
        text : display
        onTextChanged: convertInputFromJson(text)
        function convertInputFromJson(json)
        {
            var j = JSON.parse(json);
            var b = j.stringify;
            point = j["point"];
            score = j["score"];
        }
    }
}
