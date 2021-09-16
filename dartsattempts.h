#ifndef DARTSATTEMPTS_H
#define DARTSATTEMPTS_H

#include <idartsattemptvalues.h>
#include <idcmetainfo.h>

class DartsAttempts : public IDartsAttemptValues
{
public:
    DartsAttempts(const DCBuilding::IDCMetaInfo *meta):
        _attempts(meta->attempts()),_keyCode(meta->keyPoint())
    {}
    virtual int attempts() const override
    {
        return _attempts;
    }
    virtual int lastAttemptKeyCode() const override
    {
        return _keyCode;
    }
private:
    int _attempts;
    int _keyCode;
};

#endif // DARTSSUGGESTIONVALUES_H
