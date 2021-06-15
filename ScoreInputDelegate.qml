import QtQuick 2.15
import CustomItems 1.0

ScoreRectDelegate {
    id: delegate
    cellColor: "transparent"
    onTextChanged: {
        notifyCellPosition(delegate.x,delegate.y);
        var t = text;
        delegate.score = t;
    }
}
