#include "dartsinputs.h"

#include <src/FileIO/filejsonio.h>
#include <qjsondocument.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

DartsInputs::DartsInputs(IDartsIndexes* indexes, IDartPlayers *players):
        _indexes(indexes), _players(players){
        _inputsIO = new InputsIO("dartsInputs.dat");
}

void DartsInputs::init()
{
        _inputs = _inputsIO->fromFile();
}

void DartsInputs::clear()
{
        _inputs.clear();
        _inputsIO->toFile(_inputs);
}

bool DartsInputs::save(Input input)
{
        auto turnIndex = _indexes->turnIndex();
        auto playerName = _players->name(_indexes->index().playerIndex());
        input.setPlayerName(playerName);
        input.setTurnIndex(turnIndex);
        _inputs.append(input);
        return _inputsIO->toFile(_inputs);
}

QList<Input> DartsInputs::inputs(const QString& playerName, const int& turnIndex)
{
    QList<Input> playerInputs;
        for (auto& input : qAsConst(_inputs)) {
                if(input.playerName() == playerName && input.turnIndex() < turnIndex)
                        playerInputs << input;
        }
        return playerInputs;
}
