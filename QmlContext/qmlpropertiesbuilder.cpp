#include "qmlpropertiesbuilder.h"
#include <DartsStatisticsFactory/createdartsstatistics.h>
#include <PlayersContextFactory/createplayerscontext.h>
#include <LocalDartsModelsContext/localdartsmodelscontext.h>
#include <LocalDartsController/ControllerBuilder/localdartscontrollers.h>
#include <PlayerModelsContext/ContextSLA/abstractplayercontext.h>
#include <DartsModelsContext/SLAs/abstractdartscontext.h>
#include <DartsController/Controller/idartsctrl.h>
#include <DartsStatistics/SLAs/idartsstatistics.h>

class QmlPropertiesBuilder::Imp
{
public:
        Imp()
        {
                _statistics = CreateDartsStatistics().create();
                _playerContext = CreatePlayersContext().localJson();
                _dartsContext = LocalDartsModelsContext().createInstance(_playerContext);
                LocalDartsControllers dcBuilder;
                _dpController =  dcBuilder.singlePoint(_dartsContext);
                _dsController = dcBuilder.multiPoint(_dartsContext);
        }
        QmlPropertiesBuilder::Properties createProperties()
        {
                Properties _props;
                _props << createProperty<AbstractDartsContext>("dartsContext",_dartsContext);
                _props << createProperty<IDartsCtrl>("dsController",_dsController);
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
        IDartsCtrl *_dsController;
        AbstractPlayerContext *_playerContext;
        AbstractDartsContext *_dartsContext;
        IDartsStatistics *_statistics;
};

QmlPropertiesBuilder::QmlPropertiesBuilder():d(new Imp) {}

QmlPropertiesBuilder::Properties QmlPropertiesBuilder::contextProperties() const
{
    return d->createProperties();
}
