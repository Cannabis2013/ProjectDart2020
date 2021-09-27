#ifndef IDCCREATEINPUTMODEL_H
#define IDCCREATEINPUTMODEL_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCJsonSLAs/ijsonvaluesextractor.h"
#include "DartsController/DCInputSLAs/idcinputjsonkeys.h"
class IDCCreateInputModel
{
public:
    virtual DCContext::IDCInputModel *createModel(const QByteArray &json, const IDCInputJsonKeys *jsonKeys) const = 0;
    virtual DCContext::IDCInputModel *createModel(const QByteArray &json, const IDCInputJsonKeys *jsonKeys,
                                                  const QUuid &tournamentId, const QUuid &playerId, const QString &playerName) const = 0;
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const = 0;
};
#endif // IDPCMODELCREATOR_H
