#ifndef IGETDARTSSCOREBYPARAMETERS_H
#define IGETDARTSSCOREBYPARAMETERS_H


#include <qvector.h>
#include "idartsscoredb.h"

namespace DartsModelsContext {
    class IGetDartsScoreByParameters
    {
    public:
        virtual const IDartsScoreInput* getModelByParameters(const IDartsScoreDb*,
                                                             const QUuid&,
                                                             const QUuid&,
                                                             const int&) const = 0;
    };
}


#endif // IGETDARTSSCOREBYPARAMETERS_H
