#ifndef DCINPUTJSONKEYS_H
#define DCINPUTJSONKEYS_H

#include "DartsController/DCInputSLAs/idcinputjsonkeys.h"

class DCInputJsonKeys : public IDCInputJsonKeys
{
public:
    virtual QString playerId() const override
    {
        return "playerId";
    }
    virtual QString playerName() const override
    {
        return "playerName";
    }
    virtual QString modKeyCode() const override
    {
        return "modKeyCode";
    }
    virtual QString point() const override
    {
        return "point";
    }
    virtual QString score() const override
    {
        return "score";
    }
    virtual QString totalScore() const override
    {
        return "totalScore";
    }
    virtual QString tournamentId() const override
    {
        return "tournamentId";
    }
};

#endif // DCINPUTJSONKEYS_H
