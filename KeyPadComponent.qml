import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

import "componentFactory.js" as ComponentFactory

Rectangle {
    id: keyPadBody

    clip: true

    color: "silver"

    radius: 10

    signal emitScore(int val)
    signal enableKeyPad(bool enable)
    property bool enableKeys: false
    onEnableKeysChanged: {
        enableKeyPad(enableKeys);
        bullButton.enabled = enableKeys
        bullsEyeButton.enabled = enableKeys;
    }

    property PushButton doubleModifier: PushButton{}
    property PushButton trippleModifier: PushButton{}

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
       anchors.margins: 5


       rowSpacing: 1
       columnSpacing: 1

       columns: 5
       rows: 6

        Label{
            Layout.row: 0
            Layout.column: 0
            clip: true

            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.maximumHeight: 30

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop

            Layout.columnSpan: keyPadLayout.columns

            text: "Virtual keyboard"

            font.pointSize: 20
            font.bold: true

        }
        PushButton{
            id: bullButton
            backgroundColor : "black"
            hoveredColor: "black"
            textColor : "white"

            fontSize: 16

            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.row : 5
            Layout.column: 3

            buttonRadius : 5

            pressedScale: 0.75

            text: "25"

            onClicked: if(!isModifiersPressed()) handleNumberKeyPressed(text)
            enabled: false
        }

        PushButton{
            id:bullsEyeButton
            Layout.fillHeight: true
            Layout.fillWidth: true

            backgroundColor : "black"
            hoveredColor: "black"
            textColor : "white"

            fontSize: 16

            Layout.row : 5
            Layout.column: 4

            buttonRadius : 5

            pressedScale: 0.75

            text: "50"

            onClicked: if(!isModifiersPressed()) handleNumberKeyPressed(text)

            enabled: false
        }
    }
    Component.onCompleted: {
        var columnCount = keyPadLayout.columns;
        var rowCount = keyPadLayout.rows;
        var count = 0;
        var keyText = 0;
        var initialColumn = 2;

        var strings = ["D","T"];
        // Modifiers
        for(var r = 0;r < 2 ;r++){
            var selectorKey = ComponentFactory.createModifier(keyPadLayout,strings[r],1,r);
            keyPadBody.enableKeyPad.connect(selectorKey.setEnabled);
            if(selectorKey.text === "D")
            {
                selectorKey.emitCheckState.connect(keyPadBody.handleDoubleKeyPressed);
                doubleModifier = selectorKey;
            }
            else if(selectorKey.text === "T")
            {
                selectorKey.emitCheckState.connect(keyPadBody.handleTrippleKeyPressed);
                trippleModifier = selectorKey;
            }
        }
        // Numberpads
        for(var i = 1;i < rowCount && keyText < 21;i++){
            for(var j = initialColumn;j < columnCount && keyText < 21;j++){
                var numberKey = ComponentFactory.createNumberButton(keyPadLayout,keyText++,i,j);
                numberKey.emitBodyText.connect(keyPadBody.handleNumberKeyPressed);
                keyPadBody.enableKeyPad.connect(numberKey.setEnabled);
            }
            initialColumn = 0;
        }
    }
}
