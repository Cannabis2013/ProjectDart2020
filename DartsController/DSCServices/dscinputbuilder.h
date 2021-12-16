#ifndef DSCINPUTBUILDER_H
#define DSCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsController/DCScoresSLAs/absdccalcscore.h"
#include "DartsController/DCInputSLAs/dcinput.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
class DSCInputBuilder : public AbstractDCInputBuilder
{
public:
    DSCInputBuilder(AbsDCCalcScore *scoreCalc):
        AbstractDCInputBuilder(scoreCalc){}
    DCInput create(const QByteArray &json, const DCIndex &idx, const DCPlayer &player) const override
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        auto input = toInput(document.object());
        input.playerName = player.name;
        input.score = inputScoreCtx()->calc(input);
        input.remScore = player.remScore;
        input.inGame = player.in;
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
    DCInput toInput(const QJsonObject &obj, const int &initialScore = -1) const
    {
        DCInput input;
        input.playerName = obj.value("inputPlayerName").toString();
        input.score = obj.value("score").toInt();
        input.mid = obj.value("middleValue").toDouble(0);
        input.min = obj.value("minimumValue").toInt(0);
        input.max = obj.value("maximumValue").toInt(0);
        input.remScore = obj.value("remainingScore").toInt(initialScore);
        input.approved = obj.value("approved").toBool(false);
        return input ;
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
