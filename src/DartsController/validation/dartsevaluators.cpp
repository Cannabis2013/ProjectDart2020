#include "dartsevaluators.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/validation/dartsbeginnervalidator.h"
#include "src/DartsController/validation/dartsprofessionalevaluator.h"
#include "src/FileIO/filejsonio.h"
#include <QJsonDocument>
#include <QJsonObject>

DartsEvaluators::DartsEvaluators(ServiceCollection* services)
    : _services(services)
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
                return new DartsProfessionalEvaluator(_services);
        else if (_mode == 1)
                return new DartsBeginnerValidator(_services);
        return nullptr;
}
