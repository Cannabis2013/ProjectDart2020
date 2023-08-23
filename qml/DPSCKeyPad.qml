import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

import "dpscKeyPadFactory.js" as ComponentFactory
import "dpscKeyPadScripts.js" as SetupPadScripts

KeyPadInterface {
        id: keyPadBody
        onKeyClicked: sendInput(val, modifierCode)
        onEnableKeyPad: SetupPadScripts.enableHotPads(enable)

        QtObject {
                id: modPads
                property PushButton doubleModifier: PushButton {}
                property PushButton trippleModifier: PushButton {}
                property bool isDoubleModifierPressed: false
                property bool isTrippleModifierPressed: false
        }
        QtObject {
                id: hotPads
                property KeyPadItem bustPad: KeyPadItem {}
                property KeyPadItem bullPad: KeyPadItem {}
                property KeyPadItem bullsEyePad: KeyPadItem {}
        }
        onInternalKeyClicked: SetupPadScripts.processInput(value)

        GridLayout {
                id: keyPadLayout
                anchors.fill: parent
                rowSpacing: 1
                columnSpacing: 1
                columns: 5
                rows: 5
        }
        Component.onCompleted: {
                SetupPadScripts.createKeyPad()
        }
}
