#ifndef DEFAULT501JSONASSEMBLER_H
#define DEFAULT501JSONASSEMBLER_H

#include "Abstract501JsonAssembler.h"
#include <qbytearray.h>
#include "itournamentmodelscontext.h"
#include "iplayermodelscontext.h"
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <quuid.h>
class Default501JsonAssembler : public Abstract501JsonAssembler<
        QByteArray, ITournamentModelsContext,IPlayerModelsContext,QUuid>
{
    // Abstract501JsonAssembler interface
public:
    QByteArray assembleJsonFromMultiAttemptPoint(const QUuid& playerId,const QUuid& scoreId,
                                                 ITournamentModelsContext *tournamentModelsContext)
    {
        QJsonObject obj;
        obj["point"] = tournamentModelsContext->ftpScorePointValue(scoreId);
        obj["scoreValue"] = tournamentModelsContext->ftpScoreValue(scoreId);
        obj["modKeyCode"] = tournamentModelsContext->scoreKeyCode(scoreId);
        obj["playerId"] = playerId.toString(QUuid::WithoutBraces);
        auto json = QJsonDocument(obj).toJson();
        return json;
    }
    QByteArray assembleJsonFromSingleAttemptScore(const QUuid& playerId,const QUuid& scoreId,
                                                  ITournamentModelsContext *tournamentModelsContext,
                                                  IPlayerModelsContext* playerModelsContext)
    {
        QJsonObject obj;
        obj["accumulatedScoreValue"] = tournamentModelsContext->ftpScoreValue(scoreId);
        obj["modKeyCode"] = tournamentModelsContext->scoreKeyCode(scoreId);
        obj["playerName"] = playerModelsContext->playerNameFromId(playerId);
        auto json = QJsonDocument(obj).toJson();
        return json;
    }
};

#endif // DEFAULT501JSONASSEMBLER_H
