#ifndef DCSCOREJSONBUILDER_H
#define DCSCOREJSONBUILDER_H

#include "dcscoremodel.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"

class DCScoreJsonBuilder : public IDCModelJsonBuilder<const DCPlayer&>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model model) const override
    {
        obj["inputPlayerName"] = model.name;
        obj["remainingScore"] = model.remScore;
    }
};
#endif // DCSCOREJSONBUILDER_H
