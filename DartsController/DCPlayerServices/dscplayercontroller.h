#ifndef DSCPLAYERCONTROLLER_H
#define DSCPLAYERCONTROLLER_H
#include "DartsController/DCPlayerSLAs/IDCPlayerCtx.h"
#include <qstringlist.h>
class DSCPlayerController : public IDCPlayerCtx
{
public:
    virtual void set(const QStringList &names) override {_names = names;}
    virtual bool status(const QString &) const override {return true;}
    virtual bool updateStatus(const QString &, const bool &) override {return true;}
    virtual int count() const override {return _names.count();}
    virtual void reset() override{}
private:
    QStringList _names;
};
#endif // DSCPLAYERCONTROLLER_H
