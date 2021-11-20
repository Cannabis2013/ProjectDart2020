#ifndef ABSTRACTDCIDXCTRL_H
#define ABSTRACTDCIDXCTRL_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/IndexesSLAs/idcidxbuilder.h"
class AbstractDCIdxCtrl
{
public:
    virtual void init(IDartsIndex *index = nullptr) = 0;
    virtual IDartsIndex *index() const = 0;
    virtual IDartsIndex *next() = 0;
    virtual IDartsIndex *undo() = 0;
    virtual IDartsIndex *redo() = 0;
    void setCopyContext(IDCIdxBuilder *copyContext)
    {
        _copyContext = copyContext;
    }
    IDCIdxBuilder *copyContext() const
    {
        return _copyContext;
    }
    int playersCount() const
    {
        return _playerCount;
    }
    void setPlayerCount(int newPlayerCount)
    {
        _playerCount = newPlayerCount;
    }
private:
    IDCIdxBuilder *_copyContext;
    int _playerCount;
};
#endif // INDEXCONTROLLERINTERFACE_H
