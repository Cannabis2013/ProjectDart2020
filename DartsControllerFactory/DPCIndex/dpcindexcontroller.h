#ifndef DPCINDEXCONTROLLER_H
#define DPCINDEXCONTROLLER_H
#include "DCIndexSLAs/idcindexcontroller.h"
#include "Models/dcmeta.h"
class DPCIndexController : public IDCIndexController<DCIndex,DCMeta>
{
public:
    virtual void init(const DCMeta &meta) override;
    DCIndex index() const override;
    virtual DCIndex prevIndex() const override;
    void next() override;
    DCIndex undo() override;
    DCIndex redo() override;
private:
    int pCount() const;
    DCIndex _index;
    const int _attempts = 3;
    int _pCount;
};
#endif // DPCINDEXCONTROLLER_H
