#ifndef ABSTRACTDCREQIDXBUILDER_H
#define ABSTRACTDCREQIDXBUILDER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "absdcidxctrl.h"
class AbstractDCReqIdxBuilder
{
public:
    virtual DCIndex prevIdx() const = 0;
protected:
    AbsDCIdxCtrl *indexCtrl() const
    {
        return _indexController;
    }
    void setIndexCtrl(AbsDCIdxCtrl *newIndexController)
    {
        _indexController = newIndexController;
    }
private:
    AbsDCIdxCtrl *_indexController;
};
#endif // IDCREQINPUTINDEXBUILDER_H
