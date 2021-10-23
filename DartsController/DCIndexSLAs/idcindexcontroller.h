#ifndef INDEXCONTROLLERINTERFACE_H
#define INDEXCONTROLLERINTERFACE_H

class IDCIndexController
{
public:
    virtual void syncIndex() = 0;
    virtual int turnIndex() const = 0;
    virtual void setTurnIndex(const int&) = 0;
    virtual int totalIndex() const = 0;
    virtual void setTotalIndex(const int&) = 0;
    virtual int roundIndex() const = 0;
    virtual void setRoundIndex(const int&) = 0;
    virtual int setIndex() const = 0;
    virtual void setSetIndex(const int& setIndex) = 0;
    virtual int attemptIndex() const = 0;
    virtual void setAttemptIndex(const int &attemptIndex) = 0;
    virtual int numberOfAttempts() const = 0;
};

#endif // INDEXCONTROLLERINTERFACE_H
