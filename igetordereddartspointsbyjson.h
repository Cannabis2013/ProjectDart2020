#ifndef IORDEREDDARTSPOINTSBYJSON_H
#define IORDEREDDARTSPOINTSBYJSON_H

#include "idartscontrollerpoint.h"
#include <qvector.h>
#include <qbytearray.h>
#include <quuid.h>

namespace DartsPointControllerContext {
    class IGetOrderedDartsPointByJson
    {
    public:
        typedef IDartsControllerPoint<QUuid, QString,QByteArray> ControllerPoint;
        virtual QVector<const ControllerPoint*> getOrderedDartsPointsFromJson(const QByteArray &json) const = 0;
    };
}


#endif // IORDEREDDARTSPOINTSBYJSON_H
