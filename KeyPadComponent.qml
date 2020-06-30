import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

import "componentFactory.js" as ComponentFactory

Rectangle {
    id: keyPad

    clip: true

    color: "silver"

    signal emitScore(int val);

    property PushButton doubleModifier: PushButton{}
    property PushButton trippleModifier: PushButton{}

    radius: 15

    QtObject{
        id: modifiers

        property bool isDoubleModifierEnabled : false
        property bool isTrippleModifierEnabled: false
    }

    function handleNumberKeyPressed(value)
    {
        var score = value;
        if(modifiers.isDoubleModifierEnabled)
        {
            doubleModifier.clicked();
            score *= 2;
        }
        else if(modifiers.isTrippleModifierEnabled){
            trippleModifier.clicked();
            score *= 3;
        }

        emitScore(score);
    }

    function handleDoubleKeyPressed(check){
        if(modifiers.isTrippleModifierEnabled)
            trippleModifier.clicked();
        modifiers.isDoubleModifierEnabled = check;
    }
    function handleTrippleKeyPressed(check){
        if(modifiers.isDoubleModifierEnabled)
            doubleModifier.clicked();
        modifiers.isTrippleModifierEnabled = check;
    }

    function isModifiersPressed()
    {
        var doubleChecked = modifiers.isDoubleModifierEnabled;
        var trippleChecked = modifiers.isTrippleModifierEnabled;
        return doubleChecked || trippleChecked;
    }

    GridLayout{
       id: keyPadLayout

       anchors.fill: parent

       anchors.margins: 10

       columns: 11
       rows: 4

        Label{
            Layout.row: 0
            Layout.column: 0

            Layout.fillWidth: true

            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignTop

            Layout.columnSpan: keyPadLayout.columns

            Layout.preferredHeight: 40

            text: "Virtual keyboard"

            font.pointSize: 12
            font.bold: true

        }

       Rectangle{
           color: "transparent";
           Layout.fillWidth: true
           Layout.fillHeight: true
           Layout.column: 1
           Layout.row: 1
           Layout.rowSpan: 3
       }

       Rectangle{
           color: "transparent";
           Layout.fillWidth: true
           Layout.fillHeight: true
           Layout.column: 9
           Layout.row: 1
           Layout.rowSpan: 3
       }

       ColumnLayout{
           Layout.column: 10
           Layout.row: 1
           Layout.fillHeight: true
           Layout.fillWidth: true

           Layout.rowSpan: 2

           PushButton{
               Layout.fillHeight: true
               Layout.fillWidth: true

               backgroundColor : "black"
               hoveredColor: "black"
               textColor : "white"

               buttonRadius : 5

               pressedScale: 0.75

               text: "25"

               onClicked: if(!isModifiersPressed()) handleNumberKeyPressed(text)
           }

           PushButton{
               Layout.fillHeight: true
               Layout.fillWidth: true

               backgroundColor : "black"
               hoveredColor: "black"
               textColor : "white"

               buttonRadius : 5

               pressedScale: 0.75

               text: "50"

               onClicked: if(!isModifiersPressed()) handleNumberKeyPressed(text)
           }
       }
    }
    Component.onCompleted: {
        var columnCount = keyPadLayout.columns;
        var rowCount = keyPadLayout.rows;
        var count = 0;
        var keyText = 0;

        var strings = ["D","T"];
        // Modifiers
        for(var r = 2;r < rowCount;r++){
            var selectorKey = ComponentFactory.createSelectorKey(keyPadLayout,strings[r - 2],r,0);
            if(selectorKey.text === "D")
            {
                selectorKey.emitCheckState.connect(keyPad.handleDoubleKeyPressed);
                doubleModifier = selectorKey;
            }
            else if(selectorKey.text === "T")
            {
                selectorKey.emitCheckState.connect(keyPad.handleTrippleKeyPressed);
                trippleModifier = selectorKey;
            }
        }
        // Numberpads
        for(var i = 1;i < rowCount;i++){
            for(var j = 2;j < columnCount - 2;j++){
                var numberKey = ComponentFactory.createNumberButton(keyPadLayout,keyText++,i,j);
                numberKey.emitBodyText.connect(keyPad.handleNumberKeyPressed);
            }
        }
    }
}
