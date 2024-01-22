#include "dartsinputs.h"
#include <src/FileIO/filejsonio.h>

DartsInputs::DartsInputs(IDartsIndexes* indexes, IDartsPlayers* players)
{
        _indexes = indexes;
        _players = players;
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

Input DartsInputs::save(Input input)
{
        auto player = _players->one();
        auto index = _indexes->index();
        input.setPlayerName(player.name());
        input.setThrowIndex(index.throwIndex());
        _inputs << input;
        return input;
}
