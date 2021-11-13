#ifndef DCINPUTJSONBUILDER_H
#define DCINPUTJSONBUILDER_H
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class DCInputJsonBuilder : public IDCModelJsonBuilder<AbstractDartsInput*>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model input) const override
    {
        obj["point"] = input->point();
        obj["modKeyCode"] = input->modKeyCode();
        obj["score"] = input->score();
        obj["remainingScore"] = input->remainingScore();
        obj["inputPlayerId"] = input->playerId().toString(QUuid::WithoutBraces);
        obj["inputPlayerName"] = input->playerName();
        obj["middleValue"] = input->middleValue();
        obj["minimumValue"] = input->currentMinimum();
        obj["maximumValue"] = input->currentMaximum();
        obj["inGame"] = input->inGame();
        obj["approved"] = input->approved();
    }
};
#endif // DCINPUTJSONBUILDER_H
