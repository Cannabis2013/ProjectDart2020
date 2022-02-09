#ifndef QMLPROPERTIESBUILDER_H
#define QMLPROPERTIESBUILDER_H
#include "createdartscontext.h"
#include "createdartscontroller.h"
#include "createplayerscontext.h"
#include "createdartsstatistics.h"
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include "ContextSLA/absplactx.h"
#include "SLAs/absdartsctx.h"
#include "ControllerSLA/idartsctrl.h"
#include "SLAs/idartsstatistics.h"

class QmlPropertiesBuilder
{
public:
    typedef QQmlContext::PropertyPair Property;
    typedef QVector<Property> Properties;
    QmlPropertiesBuilder()
    {
        _statistics = CreateDartsStatistics().create();
        _playerContext = CreatePlayersContext().localJson();
        _dartsContext = CreateDartsContext().localJson(_playerContext);
        CreateDartsController dcBuilder;
        _dpController =  dcBuilder.pointCtrl();
        _dsController = dcBuilder.scoreCtrl();
        _dpController->setModelsContext(_dartsContext);
        _dsController->setModelsContext(_dartsContext);
    }
    Properties contextProperties() const
    {
        Properties _props;
        _props << createProperty<AbsDartsCtx>("dartsContext",_dartsContext);
        _props << createProperty<IDartsCtrl>("dsController",_dsController);
        _props << createProperty<IDartsCtrl>("dpController",_dpController);
        _props << createProperty<AbsPlaCtx>("playersContext",_playerContext);
        _props << createProperty<IDartsStatistics>("Statistics",_statistics);
        return _props;
    }
private:
    template<typename T>
    Property createProperty(const QString &name, T *value) const
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
#endif // QMLAPPLICATIONPROPERTIES_H
