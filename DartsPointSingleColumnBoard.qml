import QtQuick 2.0
import CustomItems 1.0

import "dartspointsinglecolumnboardscripts.js" as PointSingleColumnBoardScripts

ScoreBoard {
    id: scoreBoardBody
    onWidthChanged: PointSingleColumnBoardScripts.updateScoreBoard()
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
    signal takeData(int row, int column,string playerName)
    // Manipulate state such as: add score, takescore, edit score
    onSetData: PointSingleColumnBoardScripts.setData(playerName,point,score)
    onTakeData: PointSingleColumnBoardScripts.takeData(row,column,playerName)
    onClearData: datamodel.clearData();
    // Header related
    horizontalHeaderFontSize: 16
    onHorizontalHeaderFontSizeChanged: multiAttemptDataModel.headerFontSize = scoreBoardBody.horizontalHeaderFontSize
    verticalHeaderVisible: true
    onAppendHeaderData: PointSingleColumnBoardScripts.setHeaderData(data,defaultVal)
    verticalHeaderFontSize: dataValues.headerFontSize
    // Cell related
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: PointSingleColumnBoardScripts.setViewPosition(x,y)
    onAppendHeader: PointSingleColumnBoardScripts.appendHeader(header)

    QtObject{
        id: cellPositionHolder
        property int px: -1
        property int py: -1
        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return datamodel.columnWidthAt(column);
    }

    rowHeightProvider: function(row)
    {
        return datamodel.rowHeightAt(row);
    }

    model: DartsPointSingleColumnDataModel{
        id: datamodel
        onDataChanged: PointSingleColumnBoardScripts.updateScoreBoard();
        scoreFontPointSize: dataValues.scoreFontSize
        scale: dataValues.sizeScale
        headerFontSize: dataValues.headerFontSize
    }
    cellDelegate: PointInputDelegate {
        id: delegate
        cellBorderWidth: scoreBoardBody.cellBorderWidth
        cellColor: dataValues.delegateBackgroundColor
        pointFontSize: dataValues.pointFontSize
        radius: dataValues.delegateBorderRadius
        scoreFontSize: dataValues.scoreFontSize
        text: display
    }
}
