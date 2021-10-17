#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H

#include "DartsController/DCInputSLAs/idcinput.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IDCInputBuilder
{
public:
    virtual IDCInput *buildInput(const QByteArray &json) const = 0;
    virtual IDCInput *buildInput(const DCContext::DCScoreModel &scoreModel) const = 0;
    virtual QVector<IDCInput*> buildInputs(IDCScoresService *scoresService) const = 0;
    virtual QVector<IDCInput*> buildInputs(const QByteArray &json) const = 0;
};
#endif // IDPCMODELCREATOR_H
