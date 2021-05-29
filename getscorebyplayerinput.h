#ifndef GETSCOREBYPLAYERINPUT_H
#define GETSCOREBYPLAYERINPUT_H

#include "iunaryservice.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreMultiAttemptContext {
    class GetScoreByPlayerInput : public IUnaryService<const QByteArray&, int>
    {
    public:
        int service(const QByteArray& json) override
        {
            auto jsonObject = QJsonDocument::fromJson(json).object();
            auto inputValueModel = jsonObject.value("score").toInt();
            return inputValueModel;
        }
    };
}

#endif // GETSCOREBYPLAYERINPUT_H
