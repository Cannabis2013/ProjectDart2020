import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dartspointsinglecolumnscripts.js" as PointSingleColumnScripts
import "pointsinglecolumnstatescripts.js" as PointStateScripts

QtObject{
    id: dartsPointSingleColumnMetaValues
    property string title: ""
    property int keyPoint: 501
    property int attempts: 3
    property string winnerName: ""
    property var assignedPlayerNames: []
}
