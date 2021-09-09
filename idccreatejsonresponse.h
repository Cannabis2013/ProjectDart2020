#ifndef IDCCREATEJSONRESPONSE_H
#define IDCCREATEJSONRESPONSE_H
#include <dcturnvalues.h>
#include <idcindexes.h>
#include <idcindexestojson.h>
#include <idcinputstojson.h>
#include <idcmodel.h>
#include <idcturnvaluestojson.h>
#include <quuid.h>
#include "genericjsonbuilder.h"
class IDCJsonResponseBuilder
{
public:
    virtual QByteArray createJsonResponse(const QUuid &winnerId,
                                          const QString &winnerName,
                                          const QUuid &tournamentId) = 0;
    virtual QByteArray createJsonResponse(DCContext::IDCModel *inputModel,
                                          const DCContext::DCTurnValues* turnValues,
                                          const IDCInputsToJson *inputToJson,
                                          const IDCTurnValuesToJson *turnValuesToJson) = 0;
    virtual QByteArray createJsonResponse(DCContext::IDCModel *inputModel,
                                          const QUuid &tournamentId,
                                          const IDCInputsToJson *inputToJson,
                                          const DCContext::IDCIndexes *indexes,
                                          const IDCIndexesToJson *indexesToJson) = 0;
};
#endif // IDCCREATEJSONRESPONSE_H
