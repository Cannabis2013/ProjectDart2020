#ifndef QMLPROPERTIESBUILDER_H
#define QMLPROPERTIESBUILDER_H
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include "PlayerModelsContext/createplayerscontext.h"
#include "DartsController/DPController/createdpc.h"
#include "DartsController/DSController/createdsc.h"
#include "DartsModelsContext/Services/dartscontextbuilder.h"
#include "DartsControllerBuilder/Services/createdartscontroller.h"
#include "DartsController/Controller/dartscontroller.h"
class QmlPropertiesBuilder
{
public:
    typedef QQmlContext::PropertyPair Property;
    typedef QVector<Property> Properties;
    QmlPropertiesBuilder()
    {
        _playerContext = CreatePlayersContext().createLocalContext();
        _dartsContext = DartsContextBuilder().create()->setPlayersContext(_playerContext);
        CreateDartsController dcBuilder;
        _dpController = dcBuilder.createDartsPointController()->setModelsContext(_dartsContext);
        _dsController = dcBuilder.createDartsScoreController()->setModelsContext(_dartsContext);
    }
    Properties contextProperties() const
    {
        Properties _props;
        _props << createProperty<AbstractDartsContext>("dartsContext",_dartsContext);
        _props << createProperty<AbstractDartsController>("dsController",_dsController);
        _props << createProperty<AbstractDartsController>("dpController",_dpController);
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
    AbstractDartsController *_dpController;
    AbstractDartsController *_dsController;
    AbstractPlayersContext *_playerContext;
    AbstractDartsContext *_dartsContext;
};
#endif // QMLAPPLICATIONPROPERTIES_H
