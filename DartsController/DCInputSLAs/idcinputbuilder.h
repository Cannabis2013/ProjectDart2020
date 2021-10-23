#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
#include "DartsController/DCScoresSLAs/idcgetscore.h"
class IDCInputBuilder
{
public:
    virtual DCInput buildInput(const QByteArray &json, const int &initialScore = -1) const = 0;
    virtual DCInput buildInput(const QByteArray &json, const IDCPlayerService *playerContext,
                               const IDCGetScore *getScoreContext, const IDCIndexController *indexContext,
                               IDCScoresService *scoresContext) const = 0;
    virtual DCInput buildInput(const DCScoreModel &scoreModel) const = 0;
    virtual QVector<DCInput> buildInputs(IDCScoresService *scoresService) const = 0;
    virtual QVector<DCInput> buildInputs(const QByteArray &json) const = 0;
};
#endif // IDPCMODELCREATOR_H
