#include "dartsinputs.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <qjsondocument.h>
#include <src/FileIO/filejsonio.h>

DartsInputs::DartsInputs(IDartsIndexes* indexes, IDartsPlayers* players)
{
        _indexes = indexes;
        _players = players;
        _inputsIO = new InputsIO("dartsInputs.dat");
}

void DartsInputs::init()
{
        _inputs = QList<Input>();
}

void DartsInputs::setInputs(const QList<Input>& inputs)
{
        _inputs = inputs;
}

void DartsInputs::initFromFile()
{
        _inputs = _inputsIO->fromFile();
}

const QList<Input>& DartsInputs::inputs() const
{
        return _inputs;
}

QList<Input> DartsInputs::inputs(const QString& playerName, const int& throwIndex) const
{
        QList<Input> playerInputs;
        for (auto& input : qAsConst(_inputs)) {
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

bool DartsInputs::saveState()
{
        return _inputsIO->toFile(_inputs);
}
