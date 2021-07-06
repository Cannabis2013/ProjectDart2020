#ifndef ICREATEINPUTMODELSFROMJSON_H
#define ICREATEINPUTMODELSFROMJSON_H

#include "icreatefromjson.h"
#include "iplayerinput.h"
#include <qvector.h>

namespace DartsDbContext {
    class ICreateInputModelsFromJson : public ICreateFromJson<QVector<const IPlayerInput*>>
    {
    public:
        virtual QVector<const IPlayerInput*>  create(const QByteArray &json) const override = 0;
    };
}

#endif // ICREATEDARTSPOINTMODELFROMJSON_H
