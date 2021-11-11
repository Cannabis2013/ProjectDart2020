#ifndef QMLAPPLICATIONPROPERTIES_H
#define QMLAPPLICATIONPROPERTIES_H
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include "DartsController/DPController/createdpc.h"
#include "DartsController/DSController/createdsc.h"
#include "DartsModelsContext/Services/dartscontextbuilder.h"
#include "DartsControllerBuilder/Services/createdartscontroller.h"
#include "DartsController/Controller/dartscontroller.h"
#include "ModelsContext/ModelsContextSLAs/imodelscontextbuilder.h"
class QmlApplicationProperties
{
public:
    typedef QQmlContext::PropertyPair Property;
    typedef QVector<Property> Properties;
    QmlApplicationProperties()
    {
        _dartsContext = _dartsContextBuilder->create();
        _dpController = _dcBuilder->createDartsPointController(_dartsContext);
        _dsController = _dcBuilder->createDartsScoreController(_dartsContext);
    }
    Properties contextProperties() const
    {
        Properties _props;
        _props << createProperty<AbstractDartsContext>("dartsContext",dynamic_cast<AbstractDartsContext*>(_dartsContext));
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
    CreateDartsController *_dcBuilder = new CreateDartsController;
    IModelsContextBuilder *_dartsContextBuilder = new DartsContextBuilder;
    AbstractDartsController *_dpController;
    AbstractDartsController *_dsController;
    AbstractModelsContext *_dartsContext;
};
#endif // QMLAPPLICATIONPROPERTIES_H
