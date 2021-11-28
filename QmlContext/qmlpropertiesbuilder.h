#ifndef QMLPROPERTIESBUILDER_H
#define QMLPROPERTIESBUILDER_H
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include "PlayerModelsContext/createplayerscontext.h"
#include "DartsModelsContext/Services/createdartscontext.h"
#include "DartsControllerBuilder/Services/createdtsctrl.h"
#include "DartsController/Controller/dartsctrl.h"
class QmlPropertiesBuilder
{
public:
    typedef QQmlContext::PropertyPair Property;
    typedef QVector<Property> Properties;
    QmlPropertiesBuilder()
    {
        _playerContext = CreatePlayersContext().localJson();
        _dartsContext = CreateDartsContext().localJson(_playerContext);
        CreateDtsCtrl dcBuilder;
        _dpController = dcBuilder.pointCtrl()->setModelsContext(_dartsContext);
        _dsController = dcBuilder.scoreCtrl()->setModelsContext(_dartsContext);
    }
    Properties contextProperties() const
    {
        Properties _props;
        _props << createProperty<AbstractDtsCtx>("dartsContext",_dartsContext);
        _props << createProperty<AbstractDartsCtrl>("dsController",_dsController);
        _props << createProperty<AbstractDartsCtrl>("dpController",_dpController);
        _props << createProperty<AbstractPlayersContext>("playersContext",_playerContext);
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
    AbstractDartsCtrl *_dpController;
    AbstractDartsCtrl *_dsController;
    AbstractPlayersContext *_playerContext;
    AbstractDtsCtx *_dartsContext;
};
#endif // QMLAPPLICATIONPROPERTIES_H
