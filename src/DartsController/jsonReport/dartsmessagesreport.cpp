#include "dartsmessagesreport.h"
#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/jsonReport/MessageTargetRow.h"
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
        auto message = messageTargetRow();
        if (!message.hasRow())
                return arr;
        arr << message.jsonobject();
        return arr;
}

MessageTargetRow DartsMessagesReport::messageTargetRow() const
{
        auto index = _indexes->index();
        auto remaining = _scores->score().playerScore();
        auto row = _finishes->suggestTargetRow(remaining, index.turnIndex());
        return { row };
}
