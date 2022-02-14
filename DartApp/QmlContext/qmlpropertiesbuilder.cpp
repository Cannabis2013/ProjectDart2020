#include "qmlpropertiesbuilder.h"
#include "createdartscontext.h"
#include "ControllerBuilder/createdartscontroller.h"
#include "createplayerscontext.h"
#include "createdartsstatistics.h"
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include "ContextSLA/absplactx.h"
#include "SLAs/absdartsctx.h"
#include "Controller/idartsctrl.h"
#include "SLAs/idartsstatistics.h"

class QmlPropertiesBuilder::Imp
{
public:
    Imp()
    {
        _statistics = CreateDartsStatistics().create();
        _playerContext = CreatePlayersContext().localJson();
        _dartsContext = CreateDartsContext().localJson(_playerContext);
        CreateDartsController dcBuilder;
        _dpController =  dcBuilder.pointCtrl(_dartsContext);
        _dsController = dcBuilder.scoreCtrl(_dartsContext);
    }
    QmlPropertiesBuilder::Properties createProperties()
    {
        Properties _props;
        _props << createProperty<AbsDartsCtx>("dartsContext",_dartsContext);
        _props << createProperty<IDartsCtrl>("dsController",_dsController);
        _props << createProperty<IDartsCtrl>("dpController",_dpController);
        _props << createProperty<AbsPlaCtx>("playersContext",_playerContext);
        _props << createProperty<IDartsStatistics>("statistics",_statistics);
        return _props;
    }
private:
    template<typename T> Property createProperty(const QString &name, T *value) const
    {
        Property p;
        p.name = name;
        p.value = QVariant::fromValue<T*>(value);
        return p;
    }
    IDartsCtrl *_dpController;
    IDartsCtrl *_dsController;
    AbsPlaCtx *_playerContext;
    AbsDartsCtx *_dartsContext;
    IDartsStatistics *_statistics;
};

QmlPropertiesBuilder::QmlPropertiesBuilder():d(new Imp) {}

QmlPropertiesBuilder::Properties QmlPropertiesBuilder::contextProperties() const
{
    return d->createProperties();
}
