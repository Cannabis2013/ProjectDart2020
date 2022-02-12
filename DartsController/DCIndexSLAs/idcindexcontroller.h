#ifndef IDCINDEXCONTROLLER_H
#define IDCINDEXCONTROLLER_H
struct DCIndex;
struct DCMeta;
template<typename TIndex, typename TMeta>
class IDCIndexController
{
public:
    typedef TIndex Index;
    typedef TMeta Meta;
    virtual void init(const Meta &meta) = 0;
    virtual Index index() const = 0;
    virtual Index prevIndex() const = 0;
    virtual void next() = 0;
    virtual Index undo() = 0;
    virtual Index redo() = 0;
};
#endif // INDEXCONTROLLERINTERFACE_H
