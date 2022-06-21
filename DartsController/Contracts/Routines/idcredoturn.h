#ifndef IDCREDOTURN_H
#define IDCREDOTURN_H
class QByteArray;
struct DCInput;
class IDCRedoTurn
{
public:
    virtual QByteArray redo() = 0;
};

#endif // IDCREDOTURN_H
