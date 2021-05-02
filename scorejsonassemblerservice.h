#ifndef SCOREJSONASSEMBLERSERVICE_H
#define SCOREJSONASSEMBLERSERVICE_H

#include "iunary.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class ScoreJsonAssemblerService : public
        IUnary<const QByteArray&,int>
{
public:
    int service(const QByteArray& json) override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto score = jsonObject.value("score").toInt();
        return score;
    }
};

#endif // SCOREJSONASSEMBLERSERVICE_H
