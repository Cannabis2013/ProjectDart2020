#ifndef DCJSONRESPONSEBUILDER_H
#define DCJSONRESPONSEBUILDER_H
#include "idccreatejsonresponse.h"
#include "jsonmerger.h"
class DCJsonResponseBuilder : public IDCJsonResponseBuilder
{
public:
    QByteArray createJsonResponse(const QUuid &winnerId,
                                  const QString &winnerName,
                                  const QUuid &tournamentId) override
    {
        return JsonMerger::createJsonFromList({GenericJsonBuilder::createJson(winnerId,"winnerId"),
                                               GenericJsonBuilder::createJson(winnerName,"winnerName"),
                                               GenericJsonBuilder::createJson(tournamentId,"tournamentId")});
    }
    QByteArray createJsonResponse(DCContext::IDCInputModel *inputModel,
                                  const DCContext::DCTurnValues* turnValues,
                                  const IDCInputsToJson *inputToJson,
                                  const IDCTurnValuesToJson *turnValuesToJson) override
    {
        return JsonMerger::createJsonFromList({
                     inputToJson->createJson(inputModel),
                     turnValuesToJson->create(turnValues)});
    }
    QByteArray createJsonResponse(DCContext::IDCInputModel *inputModel,
                                  const QUuid &tournamentId,
                                  const IDCInputsToJson *inputToJson,
                                  const DCContext::IDCIndexes *indexes,
                                  const IDCIndexesToJson *indexesToJson) override
    {
        return JsonMerger::createJsonFromList({
                        GenericJsonBuilder::createJson(tournamentId,"tournamentId"),
                        inputToJson->createJson(inputModel),
                        indexesToJson->toJson(indexes)});
    }
};
#endif // DSCJSONRESPONSEBUILDER_H
