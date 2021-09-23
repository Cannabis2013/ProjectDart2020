#ifndef IDCCREATEJSONRESPONSE_H
#define IDCCREATEJSONRESPONSE_H
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCIndexSLAs/idcindexes.h"
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include "DartsController/DCInputSLAs/idcinputstojson.h"
#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h"
#include <quuid.h>
#include "genericjsonbuilder.h"
class IDCJsonResponseBuilder
{
public:
    virtual QByteArray createJsonResponse(const QUuid &winnerId,
                                          const QString &winnerName,
                                          const QUuid &tournamentId) = 0;
    virtual QByteArray createJsonResponse(DCContext::IDCInputModel *inputModel,
                                          const DCContext::DCTurnValues* turnValues,
                                          const IDCInputsToJson *inputToJson,
                                          const IDCTurnValuesToJson *turnValuesToJson) = 0;
    virtual QByteArray createJsonResponse(DCContext::IDCInputModel *inputModel,
                                          const QUuid &tournamentId,
                                          const IDCInputsToJson *inputToJson,
                                          const DCContext::IDCIndexes *indexes,
                                          const IDCIndexesToJson *indexesToJson) = 0;
};
#endif // IDCCREATEJSONRESPONSE_H
