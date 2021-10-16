#ifndef IDCINPUT_H
#define IDCINPUT_H
#include <quuid.h>
class IDCInput
{
public:
    virtual ~IDCInput() = default;
    virtual int point() const = 0;
    virtual void setPoint(const int& point) = 0;
    virtual int score() const = 0;
    virtual void setScore(const int& score) = 0;
    virtual QUuid playerId() const = 0;
    virtual void setPlayerId(const QUuid& id) = 0;
    virtual QString playerName() const = 0;
    virtual void setPlayerName(const QString &name) = 0;
    virtual int remainingScore() const = 0;
    virtual void setTotalScore(const int& score) = 0;
    virtual int modKeyCode() const = 0;
    virtual void setModKeyCode(const int& keyCode) = 0;
    virtual bool approved() const = 0;
    virtual void setApproved(const bool &approved) = 0;
};
#endif // IDARTSCONTROLLERPOINT_H
