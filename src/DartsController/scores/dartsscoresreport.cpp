#include "dartsscoresreport.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/idartsscores.h"
#include <QJsonObject>

DartsScoresReport::DartsScoresReport(IDartsScores* scores)
    : _scores(scores)
{
}

QJsonObject DartsScoresReport::report() const
{
        QJsonObject jsonObj;
        jsonObj["scores"] = _scores->scores().jsonArray();
        jsonObj["initialScore"] = _scores->initialScore();
        return jsonObj;
}
