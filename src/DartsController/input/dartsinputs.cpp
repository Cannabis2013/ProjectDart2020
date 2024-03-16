#include "dartsinputs.h"

#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/inputsio.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/servicecollection.h"

DartsInputs::DartsInputs(ServiceCollection* services)
    : _services(services)
{
        _inputsIO = new InputsIO("dartsInputs.dat");
}

void DartsInputs::initFromFile()
{
        _inputs = _inputsIO->fromFile();
}

bool DartsInputs::anyInputs(const QString& name, const int& throwIndex) const
{
        for (auto& input : std::as_const(_inputs)) {
                if (input.playerName() == name && input.throwIndex() < throwIndex)
                        return true;
        }
        return false;
}

QList<Input> DartsInputs::inputs(const QString& name) const
{
        QList<Input> playerInputs;
        for (auto& input : std::as_const(_inputs)) {
                if (input.playerName() == name)
                        playerInputs << input;
        }
        return playerInputs;
}

QList<Input> DartsInputs::inputs(const QString& name, const int& throwIndex) const
{
        QList<Input> playerInputs;
        for (auto& input : std::as_const(_inputs)) {
                if (input.playerName() == name && input.throwIndex() < throwIndex)
                        playerInputs << input;
        }
        return playerInputs;
}

void DartsInputs::remove(const std::function<bool(const Input&)>& predicate)
{
        _inputs = [this, predicate]() {
                QList<Input> filtered;
                for (const auto& input : _inputs) {
                        if (predicate(input))
                                filtered << input;
                }
                return filtered;
        }();
}

bool DartsInputs::saveState()
{
        return _inputsIO->toFile(_inputs);
}

Input DartsInputs::save(Input input)
{
        auto player = _services->players->one();
        auto index = _services->indexes->index();
        input.setPlayerName(player.name());
        input.setThrowIndex(index.throwIndex());
        _inputs << input;
        return input;
}
