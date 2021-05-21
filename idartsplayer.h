#ifndef IDARTSPLAYER_H
#define IDARTSPLAYER_H

#include <quuid.h>
#include "ijsonmodelsservice.h"

namespace DartsScoreMultiAttemptContext
{
    class IDartsPlayer : public IJsonModelsService<QByteArray>
    {
    public:
        virtual QUuid playerId() const = 0;
        virtual QString playerName() const = 0;
    };
}


#endif // IDARTSPLAYER_H
