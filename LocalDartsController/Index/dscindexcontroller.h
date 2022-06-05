#ifndef DSCINDEXCONTROLLER_H
#define DSCINDEXCONTROLLER_H

#include <DartsController/Models/dcindex.h>

#include <DartsController/Index/idcindexcontroller.h>

struct DCMeta;

class DSCIndexController : public IDCIndexController<DCIndex,DCMeta>
{
public:
    virtual void init(const DCMeta &meta) override;
    DCIndex index() const override;
    virtual DCIndex prevIndex() const override;
    DCIndex next() override;
    virtual DCIndex undo() override;
    virtual DCIndex redo() override;
private:
    int pCount() const;
    DCIndex _index;
    const int _attempts = 1;
    int _pCount;
};
#endif // DSCINDEXCONTROLLER_H
