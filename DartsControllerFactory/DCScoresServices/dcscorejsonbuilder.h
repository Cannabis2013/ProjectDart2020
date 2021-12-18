#ifndef DCSCOREJSONBUILDER_H
#define DCSCOREJSONBUILDER_H
#include "DCJsonSLAs/idcmodeljsonbuilder.h"
#include "Models/dcplayer.h"
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
