#ifndef IDARTSINDEX_H
#define IDARTSINDEX_H
class IDartsIndex
{
public:
    virtual int totalTurns() const = 0;
    virtual void setTotalTurns(const int&) = 0;
    virtual int turnIndex() const = 0;
    virtual void setTurnIndex(const int&) = 0;
    virtual int roundIndex() const = 0;
    virtual void setRoundIndex(const int&) = 0;
    virtual int playerIndex() const = 0;
    virtual void setPlayerIndex(const int&) = 0;
    virtual int attemptIndex() const = 0;
    virtual void setAttemptIndex(const int&) = 0;
};
#endif // IDARTSINDEX_H