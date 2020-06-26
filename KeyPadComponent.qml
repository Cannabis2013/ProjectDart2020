import QtQuick 2.0
import QtQuick.Layouts 1.3
import "componentFactory.js" as ComponentFactory

Rectangle {
    id: keyPad

    clip: true

    radius: 15

    QtObject{
        id: checkChecker

        property bool isDoubleChecked : false
        property bool isTrippleChecked: false
    }

    function handleNumberKeyPressed(value)
    {
        print(value);
    }

    function handleDoubleKeyPressed(check){
        checkChecker.isDoubleChecked = check;
        print(check);
    }
    function handleTrippleKeyPressed(check){
        checkChecker.isDoubleChecked = check;
        print(check);
    }

    GridLayout{
       id: keyPadLayout

       anchors.fill: parent
       anchors.margins: 20
       columns: 8
       rows: 3
    }
    Component.onCompleted: {
        var columnCount = keyPadLayout.columns;
        var rowCount = keyPadLayout.rows;
        var count = 0;
        var keyText = 0;

        var strings = ["D","T"];

        for(var r = 1;r < rowCount;r++){
            var selectorKey = ComponentFactory.createSelectorKey(keyPadLayout,strings[r - 1],r,0);
            if(selectorKey.text === "D")
                selectorKey.checkStateChanged.connect(keyPad.handleDoubleKeyPressed);
            else if(selectorKey.text === "T")
                selectorKey.checkStateChanged.connect(keyPad.handleTrippleKeyPressed);
        }

        for(var i = 0;i < rowCount;i++){
            for(var j = 1;j < columnCount;j++){
                var numberKey = ComponentFactory.createNumberButton(keyPadLayout,keyText++,i,j);
                numberKey.clickedText.connect(keyPad.handleNumberKeyPressed);
            }
        }
    }
}
