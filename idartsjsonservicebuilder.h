#ifndef IDARTSJSONSERVICEBUILDER_H
#define IDARTSJSONSERVICEBUILDER_H

#include "idartsjsonservice.h"
#include "idartspointsjsonservice.h"
#include "idartsscorejsonservice.h"

namespace DartsModelsContext {
    class IDartsJsonServiceBuilder
    {
    public:
        typedef IDartsPointsJsonService<IPlayerInput,IPlayerModelsService,IDartsPointIndexes,QByteArray> PointsJsonService;
        typedef IDartsScoreJsonService<IPlayerInput,IDartsScoreIndexes,QByteArray> ScoreJsonService;
        virtual IDartsJsonService* buildDartsJsonService() const = 0;
        virtual PointsJsonService* buildDartsPointsJsonService() const = 0;
        virtual ScoreJsonService* buildDartsScoreJsonService() const = 0;
    };
}


#endif // IDARTSJSONSERVICEBUILDER_H
