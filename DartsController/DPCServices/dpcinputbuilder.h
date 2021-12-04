#ifndef DPCINPUTBUILDER_H
#define DPCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DartsModelsContext/InputServices/dartsinput.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
class DPCInputBuilder : public AbstractDCInputBuilder
{
public:
    DPCInputBuilder(AbsDCCalcScore *scoreCalc):
        AbstractDCInputBuilder(scoreCalc){}
    DCInput create(const QByteArray &json, const DCIndex &idx, const DCPlayer &player) const override
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        auto input = toModel(document.object());
        input.playerName = player.name;
        input.score = inputScoreCtx()->calc(input);
        input.remScore = player.remScore;
        input.inGame = false;
        input.roundIndex = idx.roundIndex;
        input.setIndex = idx.setIndex;
        input.attempt = idx.attemptIndex;
        return input;
    }
    DCInput create(const int &remScore, const DCPlayer &player) const override
    {
        DCInput input;
        input.playerName = player.name;
        input.score = 0;
        input.remScore = remScore;
        input.inGame = true;
        return input;
    }
private:
    DCInput toModel(const QJsonObject &obj, const int &initialScore = -1) const
    {
        DCInput input;
        input.playerName = obj.value("inputPlayerName").toString("");
        input.score = obj.value("score").toInt(0);
        input.remScore = obj.value("remainingScore").toInt(initialScore);
        input.point = obj.value("point").toInt(0);
        input.modKeyCode = obj.value("modKeyCode").toInt(0);
        input.mid = obj.value("middleValue").toDouble(0);
        input.min = obj.value("minimumValue").toInt(0);
        input.max = obj.value("maximumValue").toInt(0);
        input.inGame = obj.value("inGame").toBool(false);
        return input;
    }
    AbstractDartsInput *toModel(const DCPlayer &scoreModel) const
    {
        auto input = new DartsInput;
        input->setPlayerName(scoreModel.name);
        input->setRemainingScore(scoreModel.remScore);
        return input;
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
