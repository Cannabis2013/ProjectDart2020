#include "dartsindexbuilder.h"
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <LocalDartsModelsContext/IndexesDbServices/dartsindex.h>

DartsIndexBuilder::Index *DartsIndexBuilder::create(const ByteArray &byteArray) const
{
    auto json = QJsonDocument::fromJson(byteArray).object();
    auto idx = new DartsIndex;
    idx->setTotalTurns(json.value("totalTurns").toInt());
    idx->setTurnIndex(json.value("turnIndex").toInt());
    idx->setRoundIndex(json.value("roundIndex").toInt());
    idx->setPlayerIndex(json.value("playerIndex").toInt());
    idx->setAttemptIndex(json.value("attemptIndex").toInt());
    return idx;
}
