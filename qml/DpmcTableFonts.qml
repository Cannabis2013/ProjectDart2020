import QtQuick 2.15
import CustomItems 1.0
import DartsTableUtils 1.0

import "dpmcheaderscripts.js" as HeaderScripts
import "dpmcboardscripts.js" as ScoreScripts

QtObject
{
    id: dpmcTableFonts
    property string headerFontFamily: "MS Sans Serif"
    property int headerFontSize: 16
    property string scoreFontFamily: "MS Sans Serif"
    property int scoreFontSize: 14
    property string pointFontFamily: "MS Sans Serif"
    property int pointFontSize: 10
}
