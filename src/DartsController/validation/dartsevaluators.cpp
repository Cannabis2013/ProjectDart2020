#include "dartsevaluators.h"
#include "src/DartsController/validation/dartsofficialvalidator.h"
#include "src/DartsController/validation/dartsoverthrowvalidator.h"
#include "src/FileIO/filejsonio.h"

DartsEvaluators::DartsEvaluators(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status)
    : _scores(scores)
    , _players(players)
    , _status(status)
{
}

IDartsEvaluator* DartsEvaluators::validator()
{
        if (!readFromFile())
                return nullptr;
        return fromMode();
}

IDartsEvaluator* DartsEvaluators::validator(const int& mode)
{
        _mode = mode;
        return fromMode();
}

bool DartsEvaluators::readFromFile()
{
        FileJsonIO in("evaluatorSettings.dat");
        auto json = in.read();
        auto jsonDoc = QJsonDocument::fromJson(json);
        if (!jsonDoc.isObject())
                return false;
        auto jsonObj = jsonDoc.object();
        _mode = jsonObj["winnerCondition"].toInt(-1);
        return true;
}

void DartsEvaluators::saveState()
{
        QJsonObject jsonObj;
        jsonObj["winnerCondition"] = _mode;
        auto jsonDoc = new QJsonDocument(jsonObj);
        auto json = jsonDoc->toJson(QJsonDocument::Compact);
        FileJsonIO out("evaluatorSettings.dat");
        out.write(json);
}

IDartsEvaluator* DartsEvaluators::fromMode()
{
        if (_mode == 0)
                return new DartsOfficialValidator(_scores, _players, _status);
        else if (_mode == 1)
                return new DartsOverthrowValidator(_scores, _players, _status);
        return nullptr;
}
