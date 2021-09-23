#ifndef IDCINDEXES_H
#define IDCINDEXES_H

namespace DCContext {
    class IDCIndexes
    {
    public:
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
        virtual int attemptIndex() const = 0;
    };
}

#endif // IDCINDEXES_H
