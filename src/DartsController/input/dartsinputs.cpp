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

QList<Input> DartsInputs::inputs(const QString& playerName, const int& throwIndex) const
{
        QList<Input> playerInputs;
        for (auto& input : std::as_const(_inputs)) {
                if (input.playerName() == playerName && input.throwIndex() < throwIndex)
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
        input.setPlayerName(_players->player().name());
        input.setThrowIndex(_indexes->index().throwIndex());
        _inputs << input;
        return input;
}
