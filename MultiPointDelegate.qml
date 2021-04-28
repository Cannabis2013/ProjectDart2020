import QtQuick 2.15
import CustomItems 1.0

import "fTPMultiScripts.js" as ScoreScripts

PointScoreRectDelegate {
    id: delegate
    pointDisplayVisible: true
    pointDisplayWidth: 20
    onTextChanged: {
        notifyCellPosition(delegate.x,delegate.y);
        processText(text);
    }

    function processText(txt)
    {
        var i = txt.indexOf(' ');
        var n = txt.length;
        var p = txt.substring(0,i);
        var s = txt.substring(i + 1,n);
        point  = p;
        score = s;
    }
}
