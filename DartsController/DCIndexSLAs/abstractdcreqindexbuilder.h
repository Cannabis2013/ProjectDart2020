#ifndef ABSTRACTDCREQINDEXBUILDER_H
#define ABSTRACTDCREQINDEXBUILDER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/IndexesSLAs/idcidxbuilder.h"
#include "abstractdcidxctrl.h"
class AbstractDCReqIndexBuilder
{
public:
    virtual IDartsIndex *prevIndex() const = 0;
    AbstractDCIdxCtrl *indexCtrl() const
    {
        return _indexController;
    }
    void setIndexCtrl(AbstractDCIdxCtrl *newIndexController)
    {
        _indexController = newIndexController;
    }
    IDCIdxBuilder *indexBuilder() const
    {
        return _indexBuilder;
    }
    void setIndexBuilder(IDCIdxBuilder *newIndexBuilder)
    {
        _indexBuilder = newIndexBuilder;
    }

private:
    AbstractDCIdxCtrl *_indexController;
    IDCIdxBuilder *_indexBuilder;
};
#endif // IDCREQINPUTINDEXBUILDER_H
