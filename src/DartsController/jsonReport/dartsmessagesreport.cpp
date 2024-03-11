#include "dartsmessagesreport.h"
#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/jsonReport/Message.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/idartsscores.h"

#include <QJsonArray>

DartsMessagesReport::DartsMessagesReport(IDartsFinishes* finishes, IDartsScores* scores, IDartsIndexes* indexes)
    : _finishes(finishes)
    , _scores(scores)
    , _indexes(indexes)
{
}

QJsonArray DartsMessagesReport::report() const
{
        QJsonArray arr;
        arr << messageTargetRow().jsonobject();
        arr << scoreDiff().jsonobject();
        return arr;
}

Message DartsMessagesReport::messageTargetRow() const
{
        auto index = _indexes->index();
        auto remaining = _scores->score().playerScore();
        auto row = _finishes->suggestTargetRow(remaining, index.turnIndex());
        return row != QString() ? row : "";
}

Message DartsMessagesReport::scoreDiff() const
{
        auto scores = _scores->scores().playerScores();
        if (scores.length() != 2)
                return QString();
        auto scoreOne = scores.at(0).score();
        auto scoreTwo = scores.at(1).score();
        auto diff = scoreTwo - scoreOne;
        return QString::number(diff >= 0 ? diff : diff * (-1));
}
