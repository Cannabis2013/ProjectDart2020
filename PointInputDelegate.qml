import QtQuick 2.0
import CustomItems 1.0

import "dartspointsinglecolumnboardscripts.js" as PointSingleColumnBoardScripts

PointDelegate {
    id: delegate
    onTextChanged: convertInputFromJson(text)
    function convertInputFromJson(json)
    {
        var j = JSON.parse(json);
        var b = j.stringify;
        point = j["point"];
        score = j["score"];
    }
}
