#ifndef INPUTSSERVICE_H
#define INPUTSSERVICE_H

#include "src/DartsController/input/Input.h"
class InputsUtility {
public:
        QList<Input> trimmed(const QList<Input>& inputs, const int& turnIndex);
        QList<Input> nullifyTurnInputs(const QList<Input>& inputs, const int& turnIndex);
};

#endif // INPUTSSERVICE_H
