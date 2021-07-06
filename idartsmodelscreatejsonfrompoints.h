#ifndef IDARTSMODELSCREATEJSONFROMPOINTS_H
#define IDARTSMODELSCREATEJSONFROMPOINTS_H

#include "icreatejsonfrom.h"
#include "iplayerinput.h"

namespace DartsModelsContext {
    class IDartsModelsCreateJsonFromPoints :
            public ICreateJsonFrom<const QVector<const IPlayerInput*>&>
    {
    public:
        virtual QByteArray createJson(const QVector<const IPlayerInput*> &models) const override = 0;
    };
}

#endif // IDARTSPOINTJSONBUILDER_H
