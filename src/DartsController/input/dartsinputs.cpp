#include "dartsinputs.h"

#include <src/FileIO/filejsonio.h>
#include <qjsondocument.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

DartsInputs::DartsInputs(IDartsIndexes* indexes, IDartsPlayers *players, IDartsInputEvaluator* evaluator){
        _indexes = indexes;
        _players = players;
        _evaluator = evaluator;
        _inputsIO = new InputsIO("dartsInputs.dat");
}

void DartsInputs::init()
{
        _inputs = _inputsIO->fromFile();
}

Input DartsInputs::evaluateAndAdd(const InputRequest& req)
{
        auto input = req.toInput();
        if(!_evaluator->isValid(input.mod(),input.point()))
                return Input();
        chop(); // Chop inputs at current turn index
        if(_evaluator->isWithinBounds(input.mod(),input.point()))
                return save(input);
        else
                return save(req.toNullified());
}

QList<Input> DartsInputs::inputs(const QString& playerName) const
{
        auto turnIndex = _indexes->turnIndex();
        QList<Input> playerInputs;
        for (auto& input : qAsConst(_inputs)) {
                if (input.playerName() == playerName && input.turnIndex() < turnIndex)
                        playerInputs << input;
        }
        return playerInputs;
}

Input DartsInputs::save(Input input)
{
        input.setPlayerName(_players->name());
        input.setTurnIndex(_indexes->turnIndex());
        _inputs << input;
        return input;
}

QList<Input> DartsInputs::inputs(const QString& playerName, const int& turnIndex) const
{
        QList<Input> playerInputs;
        for (auto& input : qAsConst(_inputs)) {
                if(input.playerName() == playerName && input.turnIndex() < turnIndex)
                        playerInputs << input;
        }
        return playerInputs;
}

bool DartsInputs::saveState()
{
        return _inputsIO->toFile(_inputs);
}

void DartsInputs::chop()
{
        auto turnIndex = _indexes->turnIndex();
        QList<Input> chopped;
        for (auto& input : qAsConst(_inputs)) {
                if (input.turnIndex() <= turnIndex)
                        chopped << input;
        }
        _inputs = chopped;
}
