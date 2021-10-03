#ifndef DCTURNVALJSONKEYS_H
#define DCTURNVALJSONKEYS_H

#include <DartsController/DCTurnValuesSLAs/iDCTurnValJsonKeys.h>

class DCTurnValJsonKeys : public IDCTurnValJsonKeys
{
    // IDCTurnValJsonKeys interface
public:
    virtual QString roundIndex() const override
    {
        return "roundIndex";
    }
    virtual QString setIndex() const override
    {
        return "setIndex";
    }
    virtual QString attemptIndex() const override
    {
        return "attemptIndex";
    }
    virtual QString canUndo() const override
    {
        return "canUndo";
    }
    virtual QString canRedo() const override
    {
        return "canRedo";
    }
    virtual QString suggestedFinish() const override
    {
        return "suggestedFinish";
    }
    virtual QString currentPlayerName() const override
    {
        return "currentPlayerName";
    }
};
#endif // DCTURNVALJSONKEYS_H
