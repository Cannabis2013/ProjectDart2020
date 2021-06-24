#ifndef IDARTSPOINTCONTROLLERINDEXES_H
#define IDARTSPOINTCONTROLLERINDEXES_H

#include "ijson.h"

namespace DartsPointControllerContext
{
    template<typename TJsonFormat>
    class IDartsPointControllerIndexes : public IJson<TJsonFormat>
    {
    public:
        typedef TJsonFormat JsonFormat;
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
        virtual int attemptIndex() const = 0;
        virtual JsonFormat toJson() const override = 0;
    };
}


#endif // IDARTSSINGLEATTEMPTINDEXES_H
