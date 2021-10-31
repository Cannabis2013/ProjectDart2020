#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCScoresSLAs/idccalcscore.h"
#include "DartsController/DCIndexServices/dcindex.h"

#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class IDCInputBuilder
{
public:
    virtual DCInput buildInput(const QByteArray &json, const int &initialScore = -1) const = 0;
    virtual DCInput buildInput(const QByteArray &json, const IDCPlayerController *playerController,
                               const IDCCalcScore *calcScoreContext,const DCIndex &index, IDCScoreModels *scoreModels) const = 0;
    virtual DCInput buildInput(const DCScoreModel &scoreModel) const = 0;
    virtual QVector<DCInput> buildInputs(IDCScoreModels *scoresService) const = 0;
    virtual QVector<DCInput> buildInputs(const QByteArray &json) const = 0;
};
#endif // IDPCMODELCREATOR_H