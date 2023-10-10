#include "inputsservice.h"

QList<Input> InputsUtility::trimmed(const QList<Input>& inputs, const int& turnIndex)
{
        QList<Input> chopped;
        if (turnIndex > 0) {
                for (auto& input : qAsConst(inputs)) {
                        if (input.throwIndex() < turnIndex)
                                chopped << input;
                }
        }
        return chopped;
}

QList<Input> InputsUtility::nullifyTurnInputs(const QList<Input>& inputs, const int& turnIndex)
{
        QList<Input> altered = inputs;
        auto turn = turnIndex;
        auto index = inputs.count() - 1;
        while (turn >= 0) {
                auto& input = altered[index];
                input.setPoint(0);
                index--;
                turn--;
        }
        return altered;
}
