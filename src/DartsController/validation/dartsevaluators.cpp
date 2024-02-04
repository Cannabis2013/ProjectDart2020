#include "dartsevaluators.h"
#include "src/DartsController/validation/dartsprofessionalevaluator.h"
#include "src/DartsController/validation/dartsbeginnervalidator.h"
#include "src/FileIO/filejsonio.h"

#include <QJsonDocument>
#include <QJsonObject>

DartsEvaluators::DartsEvaluators(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status, IScoresCalculator* calculator)
    : _scores(scores)
    , _players(players)
    , _status(status)
    , _calculator(calculator)
{
}

AbstractDartsEvaluator* DartsEvaluators::validator()
{
        if (!readFromFile())
                return nullptr;
        return fromMode();
}

AbstractDartsEvaluator* DartsEvaluators::validator(const int& mode)
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

AbstractDartsEvaluator* DartsEvaluators::fromMode()
{
        if (_mode == 0)
                return new DartsProfessionalEvaluator(_scores, _players, _status, _calculator);
        else if (_mode == 1)
                return new DartsBeginnerValidator(_scores, _players, _status);
        return nullptr;
}
