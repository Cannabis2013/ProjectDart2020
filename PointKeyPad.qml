import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

import "PointKeyPadFactory.js" as ComponentFactory
import "pointKeyPadScripts.js" as PointKeyPadScripts

KeyPadInterface {
    id: keyPadBody

    onKeyClicked: sendInput(val,modifierCode);
    onEnableKeyPad: {
        bullsButton.enabled = enable
        bullsEyeButton.enabled = enable;
    }
    property PushButton doubleModifier: PushButton{}
    property PushButton trippleModifier: PushButton{}

    QtObject{
        id: modifiers

        property bool isDoubleModifierPressed : false
        property bool isTrippleModifierPressed: false
    }

    onInternalKeyClicked :
    {
        var modifierClickCode = modifiers.isTrippleModifierPressed ? 0x2C :
                                                                   modifiers.isDoubleModifierPressed ? 0x2B :
                                                                                                       0x2A;
        if(modifierClickCode === 0x2B)
            doubleModifier.clicked();
        else if(modifierClickCode === 0x2C)
            trippleModifier.clicked();

        keyClicked(value,modifierClickCode);
    }

    GridLayout{
       id: keyPadLayout
       anchors.fill: parent
       rowSpacing: 1
       columnSpacing: 1
       columns: 5
       rows: 5

        PushButton{
            id: bullsButton
            backgroundColor : "green"
            hoveredColor: "green"
            textColor : "white"
            fontSize: 16
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.row : 4
            Layout.column: 3
            buttonRadius : 5
            pressedScale: 0.75
            text: "25"
            onClicked: if(!PointKeyPadScripts.isModifiersPressed()) PointKeyPadScripts.handleNumberKeyPressed(text)
            enabled: false
        }

        PushButton{
            id: bullsEyeButton
            Layout.fillHeight: true
            Layout.fillWidth: true
            backgroundColor : "red"
            hoveredColor: "red"
            textColor : "white"
            fontSize: 16
            Layout.row : 4
            Layout.column: 4
            buttonRadius : 5
            pressedScale: 0.75
            text: "50"
            onClicked: if(!PointKeyPadScripts.isModifiersPressed()) PointKeyPadScripts.handleNumberKeyPressed(text)
            enabled: false
        }
    }
    Component.onCompleted: {
        PointKeyPadScripts.assembleKeyPad();
    }
}
