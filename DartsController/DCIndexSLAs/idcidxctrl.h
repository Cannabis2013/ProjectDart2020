#ifndef IDCIDXCTRL_H
#define IDCIDXCTRL_H
class DCIndex;
class DCMeta;
class IDCIdxCtrl
{
public:
    virtual void init(const DCMeta &meta) = 0;
    virtual DCIndex index() const = 0;
    virtual DCIndex prevIndex() const = 0;
    virtual DCIndex next() = 0;
    virtual DCIndex undo() = 0;
    virtual DCIndex redo() = 0;
};
#endif // INDEXCONTROLLERINTERFACE_H
