import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dpscscripts.js" as DPSCScriptss
import "dpscstatescripts.js" as DPSCStateScripts

QtObject{
    id: dartsPointSingleColumnMetaValues
    property string title: ""
    property int keyPoint: 501
    property int attempts: 3
    property string winnerName: ""
    property var assignedPlayerNames: []
}
