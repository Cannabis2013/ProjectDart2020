#ifndef DARTSSCOREJSONEXTRACTOR_H
#define DARTSSCOREJSONEXTRACTOR_H

#include "idartsjsonextractor.h"
#include "QString"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreMultiAttemptContext {
    class DartsScoreJsonExtractor : public IDartsJsonExtractor<QByteArray,QString>
    {
    public:
        StringFormat getWinnerNameByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto winnerName = jsonObject.value("playerName").toString();
            return winnerName;
        }
        int getPlayerScoreByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto score = jsonObject.value("score").toInt();
            return score;
        }
    };
}

#endif // DARTSSCOREJSONEXTRACTOR_H
