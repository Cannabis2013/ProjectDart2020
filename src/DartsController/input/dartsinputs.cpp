#include "dartsinputs.h"
#include <src/FileIO/filejsonio.h>

using namespace std;

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
        for (auto& input : as_const(_inputs)) {
                if (input.playerName() == playerName && input.throwIndex() < throwIndex)
                        playerInputs << input;
        }
        return playerInputs;
}

Input DartsInputs::save(Input input)
{
        input.setPlayerName(_players->name());
        input.setThrowIndex(_indexes->index().throwIndex());
        _inputs << input;
        return input;
}
