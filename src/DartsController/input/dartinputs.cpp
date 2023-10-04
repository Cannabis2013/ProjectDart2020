#include "dartinputs.h"

#include <src/FileIO/filejsonio.h>
#include <qjsondocument.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

DartInputs::DartInputs(IDartIndexes* indexes):
        _indexes(indexes)
{
        initFromFile();
}

void DartInputs::clear()
{
        _inputs.clear();
}

bool DartInputs::save(DartInput input)
{
        auto turnIndex = _indexes->turnIndex();
        input.setTurnIndex(turnIndex);
        _inputs.append(input);
        return writeToFile();
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

bool DartInputs::writeToFile()
{
        FileJsonIO jsonIO("dartInputs.dat");
        QJsonArray jsonArr;
        for (auto input : qAsConst(_inputs))
                jsonArr.append(input.toJsonObject());
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson());
}

void DartInputs::initFromFile()
{
        FileJsonIO jsonIO("dartInputs.dat");
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        if(!jsonDoc.isArray())
                return;
        auto arr = jsonDoc.array();
        for (auto ite = arr.begin(); ite != arr.end(); ++ite) {
                auto jsonObj = ite->toObject();
                _inputs.append(DartInput::fromJson(jsonObj));
        }
}
