#ifndef IDCTURNVALJSONKEYS_H
#define IDCTURNVALJSONKEYS_H

#include <qstring.h>

class IDCTurnValJsonKeys
{
public:
    virtual QString roundIndex() const = 0;
    virtual QString setIndex() const = 0;
    virtual QString attemptIndex() const = 0;
    virtual QString canUndo() const = 0;
    virtual QString canRedo() const = 0;
    virtual QString suggestedFinish() const = 0;
    virtual QString currentPlayerName() const = 0;
};
#endif // IDCTURNVALJSONKEYS_H
