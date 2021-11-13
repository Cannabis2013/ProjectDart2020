#ifndef DCSCOREJSONBUILDER_H
#define DCSCOREJSONBUILDER_H

#include "dcscoremodel.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"

class DCScoreJsonBuilder : public IDCModelJsonBuilder<const DCScoreModel&>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model model) const override
    {
        obj["inputPlayerId"] = model.playerId.toString(QUuid::WithoutBraces);
        obj["inputPlayerName"] = model.playerName;
        obj["remainingScore"] = model.remainingScore;
    }
};
#endif // DCSCOREJSONBUILDER_H
