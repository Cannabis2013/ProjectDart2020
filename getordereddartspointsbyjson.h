#ifndef GETORDEREDDARTSPOINTSBYJSON_H
#define GETORDEREDDARTSPOINTSBYJSON_H

#include "igetordereddartspointsbyjson.h"
#include "dartscontrollerpoint.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsPointControllerContext {
    class GetOrderedDartsPointsByJson : public IGetOrderedDartsPointByJson
    {
    public:
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> DartsPoint;
        QVector<const ControllerPoint *> getOrderedDartsPointsFromJson(const QByteArray &json) const override;
    };
}

#endif // GETORDEREDDARTSPOINTSBYJSON_H
