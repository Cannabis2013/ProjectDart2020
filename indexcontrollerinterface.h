#ifndef INDEXCONTROLLERINTERFACE_H
#define INDEXCONTROLLERINTERFACE_H

class IndexControllerInterface
{
public:
    virtual void setIndexes(const int&,
                            const int&,
                            const int&,
                            const int&,
                            const int&) = 0;
    virtual void reset() = 0;
    virtual void next() = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual bool canUndo() = 0;
    virtual bool canRedo() = 0;

    virtual void syncIndex() = 0;

    virtual int turnIndex() = 0;
    virtual void setTurnIndex(const int&) = 0;
    virtual int totalIndex() = 0;
    virtual void setTotalIndex(const int&) = 0;
    virtual int roundIndex() = 0;
    virtual void setRoundIndex(const int&) = 0;
    virtual int setIndex() = 0;
    virtual void setSetIndex(const int& setIndex) = 0;
    virtual int attempt() = 0;
    virtual void setAttempt(const int&) = 0;

    virtual int numberOfAttempts() = 0;
    virtual void setNumberOfAttempts(const int&) = 0;

    virtual int playersCount() = 0;
    virtual void setPlayersCount(const int&) = 0;
};

#endif // INDEXCONTROLLERINTERFACE_H
