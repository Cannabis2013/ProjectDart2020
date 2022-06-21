#ifndef IDCUNDOTURN_H
#define IDCUNDOTURN_H
class QByteArray;
class IDCUndoTurn
{
public:
    virtual QByteArray undo() = 0;
};

#endif // IDCUNDOTURN_H
