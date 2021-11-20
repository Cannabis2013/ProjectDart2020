#ifndef IDCUPDATEPLAYERSCORES_H
#define IDCUPDATEPLAYERSCORES_H
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include "DartsController/PlayerStatsSLAs/idcupdateplayerstat.h"
class IDCUpdatePlayerScores
{
public:
    virtual void update(const QVector<IModel<QUuid>*> &inputs, AbstractDCScoresCtx *scoresService) const = 0;
};
#endif // IDARTSSUBTRACTSCORES_H
