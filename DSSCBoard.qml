import QtQuick 2.15
import CustomItems 1.0

import "dartsscorescoreboardscripts.js" as ScoreScripts

ScoreBoard {
    id: scoreSingleColumnBody
    onWidthChanged: ScoreScripts.updateScoreBoard()
    // Fonts
    QtObject{
        id: dataValues
        readonly property int scoreFontSize: 32
        readonly property double sizeScale: 1.2
        readonly property color delegateBackgroundColor: "green"
        readonly property int delegateBorderRadius: 10
        readonly property int headerFontSize: 16
    }

    // Data related
    signal setData(string playerName, int score)
    signal takeData(int row, int column,string playerName)
    signal editData(int row, int column,int score)
    // Manipulate state such as: add score, takescore, edit score
    onSetData: ScoreScripts.setData(playerName,score)
    onTakeData: ScoreScripts.takeData(row,column,playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)
    onClearData: multiAttemptDataModel.clearData();
    // Header related
    verticalHeaderVisible: true
    onAppendHeaderData: ScoreScripts.setHeaderData(data,defaultVal)
    // Cell related
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)
    onAppendHeader: ScoreScripts.appendHeader(data)

    QtObject{
        id: cellPositionHolder
        property int px: -1
        property int py: -1
        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return multiAttemptDataModel.columnWidthAt(column);
    }

    rowHeightProvider: function(row)
    {
        return multiAttemptDataModel.rowHeightAt(row);
    }

    model: DSMCTableModel{
        id: multiAttemptDataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        scoreFontPointSize: dataValues.scoreFontSize
        scale: dataValues.sizeScale
        headerFontSize: dataValues.headerFontSize
    }
    cellDelegate: ScoreInputDelegate {
        id: delegate
        text: display
        scoreFontSize: dataValues.scoreFontSize
        cellBorderWidth: scoreSingleColumnBody.cellBorderWidth
        cellColor: dataValues.delegateBackgroundColor
        cellBorderRadius: dataValues.delegateBorderRadius
    }
}
