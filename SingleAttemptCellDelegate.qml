import QtQuick 2.15
import CustomItems 1.0

PointInputDelegate {
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
        point = txt.substring(0,i);
        score = txt.substring(i + 1,n);
    }
}
