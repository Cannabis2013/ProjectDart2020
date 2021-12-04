#ifndef ABSDCIDXCTRL_H
#define ABSDCIDXCTRL_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/IndexesSLAs/idcidxconverter.h"
#include "dcindex.h"
class AbsDCIdxCtrl
{
public:
    virtual void init(const DCIndex &index = DCIndex()) = 0;
    virtual DCIndex index() const = 0;
    virtual DCIndex next() = 0;
    virtual DCIndex undo() = 0;
    virtual DCIndex redo() = 0;
    int playersCount() const
    {
        return _playerCount;
    }
    void setPlayerCount(int newPlayerCount)
    {
        _playerCount = newPlayerCount;
    }
private:
    int _playerCount;
};
#endif // INDEXCONTROLLERINTERFACE_H
