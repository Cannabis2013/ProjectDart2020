#ifndef INDEXCONTROLLERINTERFACE_H
#define INDEXCONTROLLERINTERFACE_H

class IndexControllerInterface
{
public:
    virtual void reset() = 0;
    virtual void next() = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual bool canUndo() = 0;
    virtual bool canRedo() = 0;

    virtual void syncIndex() = 0;

    virtual int index() = 0;
    virtual int totalIndex() = 0;
    virtual int roundIndex() = 0;
    virtual int setIndex() = 0;
    virtual int attempt() = 0;
};

#endif // INDEXCONTROLLERINTERFACE_H
