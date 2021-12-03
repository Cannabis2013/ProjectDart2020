#ifndef IDCPLAYERCTX_H
#define IDCPLAYERCTX_H
#include <quuid.h>
#include <qvector.h>
class IDCPlayerCtx
{
public:
    struct Player{
        QString name;
        bool in;
    };
    typedef QVector<Player*> Players;
    virtual void set(const QStringList &names) = 0;
    virtual bool status(const QString &name) const = 0;
    virtual bool updateStatus(const QString &name, const bool &status) = 0;
    virtual int count() const = 0;
    virtual void reset() = 0;
};
#endif // IDCPLAYERCONTROLLER_H
