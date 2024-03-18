#include "dartsinputs.h"

#include "src/DartsController/input/models/Input.h"
#include "src/DartsController/input/persistence/inputsio.h"

DartsInputs::DartsInputs()
{
        _inputsIO = new InputsIO();
}

void DartsInputs::initFromFile()
{
        _inputs = _inputsIO->fromFile();
}

bool DartsInputs::anyInputs(const QString& name, const int& throwIndex) const
{
        for (auto& input : _inputs) {
                if (input.playerName() == name && input.throwId() < throwIndex)
                        return true;
        }
        return false;
}

QList<Input> DartsInputs::all() const
{
        return _inputs;
}

QList<Input> DartsInputs::inputs(const QString& name) const
{
        QList<Input> playerInputs;
        for (auto& input : _inputs) {
                if (input.playerName() == name)
                        playerInputs << input;
        }
        return playerInputs;
}

QList<Input> DartsInputs::inputs(const QString& name, const int& throwIndex) const
{
        QList<Input> playerInputs;
        for (auto& input : _inputs) {
                if (input.playerName() == name && input.throwId() < throwIndex)
                        playerInputs << input;
        }
        return playerInputs;
}

bool DartsInputs::saveState()
{
        return _inputsIO->toFile(_inputs);
}
