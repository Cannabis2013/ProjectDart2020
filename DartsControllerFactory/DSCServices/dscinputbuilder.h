#ifndef DSCINPUTBUILDER_H
#define DSCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DCInputSLAs/abstractdcinputbuilder.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
class DSCInputBuilder : public AbstractDCInputBuilder
{
public:
    DCInput create(const QByteArray &json, const DCIndex &idx, const DCPlayer &player) const override
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        auto input = toInput(document.object());
        input.playerName = player.name;
        input.score = calc(input);
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
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
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
    int calc(DCInput &input) const
    {
        auto multiplier = createPointMultiplier(input.modKeyCode);
        return calculateScore(input.point,multiplier);
    }
    int createPointMultiplier(const int &code) const
    {
        auto pointMultiplier = code == TrippleModifier ? 3 :
                               code == DoubleModifier ? 2 :
                               code == SingleModifer ? 1 : 0;
        return pointMultiplier;
    }
    int calculateScore(const int &point, const int &multiplier) const
    {
        return point*multiplier;
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
