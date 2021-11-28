#ifndef ABSTRACTDCREQIDXBUILDER_H
#define ABSTRACTDCREQIDXBUILDER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "abstractdcidxctrl.h"
class AbstractDCReqIdxBuilder
{
public:
    virtual DCIndex prevIdx() const = 0;
protected:
    AbstractDCIdxCtrl *indexCtrl() const
    {
        return _indexController;
    }
    void setIndexCtrl(AbstractDCIdxCtrl *newIndexController)
    {
        _indexController = newIndexController;
    }
private:
    AbstractDCIdxCtrl *_indexController;
};
#endif // IDCREQINPUTINDEXBUILDER_H
