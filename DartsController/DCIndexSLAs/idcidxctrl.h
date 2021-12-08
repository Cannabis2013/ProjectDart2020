#ifndef IDCIDXCTRL_H
#define IDCIDXCTRL_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/IndexesSLAs/idcidxconverter.h"
#include "dcindex.h"
class IDCIdxCtrl
{
public:
    virtual void init(const int &count, const DCIndex &index = DCIndex()) = 0;
    virtual DCIndex index() const = 0;
    virtual DCIndex prevIndex() const = 0;
    virtual DCIndex next() = 0;
    virtual DCIndex undo() = 0;
    virtual DCIndex redo() = 0;
};
#endif // INDEXCONTROLLERINTERFACE_H
