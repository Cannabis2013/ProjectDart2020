#ifndef IDSINDEXSERVICE_H
#define IDSINDEXSERVICE_H

#include <idscindexes.h>
#include <qbytearray.h>

class IDSIndexService
{
public:
    virtual void setIndexes(const DSCContext::IDSCIndexes *indexes) = 0;
    virtual void reset() = 0;
    virtual void next() = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual bool canUndo() const = 0;
    virtual bool canRedo() const = 0;

    virtual void syncIndex() = 0;

    virtual int turnIndex() const = 0;
    virtual void setTurnIndex(const int&) = 0;
    virtual int totalIndex() const = 0;
    virtual void setTotalIndex(const int&) = 0;
    virtual int roundIndex() const = 0;
    virtual void setRoundIndex(const int&) = 0;
    virtual int setIndex() const = 0;
    virtual void setSetIndex(const int& setIndex) = 0;

    virtual int numberOfAttempts() const = 0;
    virtual void setNumberOfAttempts(const int&) = 0;

    virtual int playersCount() const = 0;
    virtual void setPlayersCount(const int&) = 0;
};

#endif // IDARTSMULTIATTEMPTINDEXSERVICE_H
