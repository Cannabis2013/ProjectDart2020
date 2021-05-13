import QtQuick 2.15
import CustomItems 1.0

import "dartsMultiAttemptScripts.js" as ScoreScripts

ScoreBoard {
    id: multiAttemptScoreBoardBody
    onWidthChanged: ScoreScripts.updateScoreBoard()
    // Fonts
    QtObject{
        id: dataValues
        readonly property int scoreFontSize: 32
        readonly property double sizeScale: 1.2
        readonly property color delegateBackgroundColor: "green"
        readonly property int delegateBorderRadius: 10
    }

    // Data related
    signal setData(string playerName, int score)
    signal takeData(int row, int column,string playerName)
    signal editData(int row, int column,int score)
    // Manipulate state such as: add score, takescore, edit score
    onSetData: ScoreScripts.setData(playerName,score)
    onTakeData: ScoreScripts.takeData(row,column,playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)
    onClearData: multiAttemptScoreDataModel.clearData();
    // Header related
    horizontalHeaderFontSize: 16
    onHorizontalHeaderFontSizeChanged: multiAttemptScoreDataModel.headerFontSize = multiAttemptScoreBoardBody.horizontalHeaderFontSize
    verticalHeaderVisible: true
    onAppendHeaderData: ScoreScripts.setHeaderData(data,defaultVal)
    // Cell related
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)
    onAppendHeader: ScoreScripts.appendHeader(header)

    QtObject{
        id: cellPositionHolder
        property int px: -1
        property int py: -1
        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return multiAttemptScoreDataModel.columnWidthAt(column);
    }

    rowHeightProvider: function(row)
    {
        return multiAttemptScoreDataModel.rowHeightAt(row);
    }

    model: MultiAttemptScoreDataModel{
        id: multiAttemptScoreDataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        attempts: 1
        scoreFontPointSize: dataValues.scoreFontSize
        scale: dataValues.sizeScale
    }
    cellDelegate: SingleScoreDelegate {
        id: delegate
        text: display
        scoreFontSize: dataValues.scoreFontSize
        cellBorderWidth: multiAttemptScoreBoardBody.cellBorderWidth
        color: dataValues.delegateBackgroundColor
        cellBorderRadius: dataValues.delegateBorderRadius
    }
}
