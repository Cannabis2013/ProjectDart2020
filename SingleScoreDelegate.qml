import QtQuick 2.15
import CustomItems 1.0

CellDelegate {
    id: delegate
    cellBorderWidth: fTPBody.cellBorderWidth
    cellColor: "transparent"
    scoreFontSize: fTPBody.scoreFontSize
    pointFontSize: fTPBody.pointFontSize
    pointDisplayVisible: fTPBody.displayPoints
    pointDisplayWidth: fTPBody.pointDisplayWidth
    onTextChanged: {
        notifyCellPosition(delegate.x,delegate.y);
        var t = text;
        delegate.score = t;
    }
}
