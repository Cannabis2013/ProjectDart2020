#ifndef ITURNCONTROLLER_H
#define ITURNCONTROLLER_H

class QByteArray;

class ITurnController {
public:
        virtual QByteArray report() const = 0;
        virtual bool canUndo() const = 0;
        virtual bool canRedo() const = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
        virtual int playerNumber() const = 0;
};

#endif // ITURNCONTROLLER_H
