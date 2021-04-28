import QtQuick 2.15
import CustomItems 1.0

import "fTPSingleScripts.js" as ScoreScripts

ScoreBoard {
    id: fTPBody
    onWidthChanged: ScoreScripts.updateScoreBoard()
    // Data related
    signal setData(string playerName, int score)
    signal takeData(int row, int column,string playerName)
    signal editData(int row, int column,int score)
    // Manipulate state such as: add score, takescore, edit score
    onSetData: ScoreScripts.setData(playerName,score)
    onTakeData: ScoreScripts.takeData(row,column,playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)
    onClearData: fTPModel.clearData();

    property int attempts: 3
    onAttemptsChanged: fTPModel.attempts = attempts;

    // Header related
    horizontalHeaderFontSize: 16
    onHorizontalHeaderFontSizeChanged:
        fTPModel.headerFontSize =
        fTPBody.horizontalHeaderFontSize
    verticalHeaderVisible: false
    onAppendHeaderData: {
        for(var i = 0; i < data.length;i++)
        {
            var assignedPlayerName = data[i];
            appendHeader(assignedPlayerName,Qt.Horizontal);
            setData(assignedPlayerName,defaultVal);
        }
    }
    headerOrientation: Qt.Horizontal
    onHeaderOrientationChanged: fTPModel.setHeaderOrientation(headerOrientation)
    // Cell related
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    onAppendHeader: ScoreScripts.appendHeader(header,orientation)

    QtObject{
        id: cellPositionHolder

        property int px: -1
        property int py: -1

        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return fTPBody.width / fTPModel.columnCount;
    }

    rowHeightProvider: function(row)
    {
        return fTPBody.height;
    }

    model: SFtpDataModel{
        id: fTPModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        attempts: fTPBody.attempts
        scoreFontPointSize: 48
        horizontalFillMode: DataModelContext.fixedFill
        scale: 1
    }
    cellDelegate: SingleScoreDelegate {
        id: delegate
        text: display
        scoreFontSize: 48
    }
}
