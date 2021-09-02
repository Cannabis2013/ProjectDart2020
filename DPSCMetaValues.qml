import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dpscscripts.js" as PointSingleColumnScripts
import "dpscstatescripts.js" as PointStateScripts

QtObject{
    id: dartsPointSingleColumnMetaValues
    property string title: ""
    property int keyPoint: 501
    property int attempts: 3
    property string winnerName: ""
    property var assignedPlayerNames: []
}
