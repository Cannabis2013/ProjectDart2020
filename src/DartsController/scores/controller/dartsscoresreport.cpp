#include "dartsscoresreport.h"
#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/idartsscores.h"
#include <QJsonObject>

DartsScoresReport::DartsScoresReport(ServiceCollection* services)
    : _scores(services->scores)
    , _indexes(services->indexes)
    , _finishes(services->finishes)
{
}

QString DartsScoresReport::initialScore() const
{
        auto value = _scores->initialScore();
        return QString::number(value);
}

int DartsScoresReport::playerOne() const
{
        auto scores = _scores->scores();
        auto score = scores.playerScores().first();
        return score.score();
}

int DartsScoresReport::playerTwo() const
{
        auto scores = _scores->scores();
        auto score = scores.playerScores().last();
        return score.score();
}

QString DartsScoresReport::finishRow() const
{
        auto turnIndex = _indexes->index().turnIndex();
        auto remaining = _scores->score().playerScore();
        return _finishes->suggestTargetRow(remaining, turnIndex);
}

QString DartsScoresReport::delta() const
{
        auto scores = _scores->scores().playerScores();
        if (scores.length() != 2)
                return QString();
        auto scoreOne = scores.at(0).score();
        auto scoreTwo = scores.at(1).score();
        auto diff = scoreTwo - scoreOne;
        return QString::number(diff >= 0 ? diff : diff * (-1));
}
