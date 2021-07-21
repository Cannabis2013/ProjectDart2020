#ifndef ICREATEINPUTMODELSFROMJSON_H
#define ICREATEINPUTMODELSFROMJSON_H

#include "icreatefromjson.h"
#include "iplayerinput.h"
#include <qvector.h>

namespace DartsDbContext {
    class ICreateInputModelsFromJson : public ICreateFromJson<QVector<const IModel<QUuid>*>>
    {
    public:
        virtual QVector<const IModel<QUuid>*>  create(const QByteArray &json) const override = 0;
    };
}

#endif // ICREATEDARTSPOINTMODELFROMJSON_H
