#include "qmlpropertiesbuilder.h"
#include <PlayerModelsContext/PlayerContextWithJson/CreatePlayerContext/createplayerscontext.h>
#include <DartsModelsContext/LocalDartsModelsContext/localdartsmodelscontext.h>
#include <PlayerModelsContext/Contracts/ContextSLA/abstractplayercontext.h>
#include <DartsModelsContext/Contracts/abstractdartscontext.h>
#include <DartsStatistics/Contracts/SLAs/idartsstatistics.h>
#include <DartsController/Contracts/Controller/idartsctrl.h>
#include <DartsController/LocalDartsController/localdartscontrollers.h>
#include <DartsStatistics/DartsStatisticsImp/CreateDartsStatistics/createdartsstatistics.h>

class QmlPropertiesBuilder::Imp
{
public:
        Imp()
        {
                _statistics = CreateDartsStatistics().create();
                _playerContext = CreatePlayersContext().localJson();
                _dartsContext = LocalDartsModelsContext().createInstance(_playerContext);
                LocalDartsControllers dcBuilder;
                _dpController = dcBuilder.singlePoint(_dartsContext);
        }
        QmlPropertiesBuilder::Properties createProperties()
        {
                Properties _props;
                _props << createProperty<AbstractDartsContext>("dartsContext", _dartsContext);
                _props << createProperty<IDartsCtrl>("dpController",_dpController);
                _props << createProperty<AbstractPlayerContext>("playersContext",_playerContext);
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
        AbstractPlayerContext *_playerContext;
        AbstractDartsContext *_dartsContext;
        IDartsStatistics *_statistics;
};

QmlPropertiesBuilder::QmlPropertiesBuilder():d(new Imp) {}

QmlPropertiesBuilder::Properties QmlPropertiesBuilder::contextProperties() const
{
    return d->createProperties();
}
