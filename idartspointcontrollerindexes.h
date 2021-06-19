#ifndef IDARTSPOINTCONTROLLERINDEXES_H
#define IDARTSPOINTCONTROLLERINDEXES_H

namespace DartsPointControllerContext
{
    class IDartsPointControllerIndexes
    {
    public:
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
        virtual int attemptIndex() const = 0;
    };
}


#endif // IDARTSSINGLEATTEMPTINDEXES_H
