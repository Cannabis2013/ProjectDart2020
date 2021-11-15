#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
#include <qjsonarray.h>
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idccalcscore.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
class IDCInputBuilder
{
public:
    virtual AbstractDartsInput *create(const QByteArray &json, const IDCPlayerController *playerController,
                               const IDCCalcScore *calcScoreContext,IDartsIndex *index, IDCScoreModels *scoreModels) const = 0;
};
#endif // IDPCMODELCREATOR_H
