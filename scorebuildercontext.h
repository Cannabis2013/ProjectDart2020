#ifndef SCOREBUILDERCONTEXT_H
#define SCOREBUILDERCONTEXT_H

#include <quuid.h>
#include "iscoreparameter.h"
// ScoreBuilderCollection
namespace SBC {
    class DartsPointParameters
    {
    public:
        int pointValue;
        int scoreValue;
        int roundIndex;
        int setIndex;
        int attempt;
        int hint;
        int keyCode;
        QUuid playerId;
        QUuid tournament;
        QUuid id;
    };

    class ModelOptions
    {
    public:
        bool generateUniqueId = true;
        bool customUuid = false;
    };
}

#endif // SCOREBUILDERCONTEXT_H
