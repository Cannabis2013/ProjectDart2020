#include "dartinputs.h"

#include <src/FileIO/filejsonio.h>
#include <qjsondocument.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

DartInputs::DartInputs(IDartsIndexes* indexes):
        _indexes(indexes){
        _inputsIO = new InputsIO("dartInputs.dat");
}

void DartInputs::init()
{
        _inputs = _inputsIO->fromFile();
}

void DartInputs::clear()
{
        _inputs.clear();
        _inputsIO->toFile(_inputs);
}

bool DartInputs::save(DartInput input)
{
        auto turnIndex = _indexes->turnIndex();
        input.setTurnIndex(turnIndex);
        _inputs.append(input);
        return _inputsIO->toFile(_inputs);
}

QList<DartInput> DartInputs::inputs()
{
        return _inputs;
}

QList<DartInput> DartInputs::inputs(const QString& playerName, const int& turnIndex)
{
        QList<DartInput> playerInputs;
        for (auto& input : qAsConst(_inputs)) {
                if(input.playerName() == playerName && input.turnIndex() <= turnIndex)
                        playerInputs << input;
        }
        return playerInputs;
}
