#ifndef DEFAULTMODELSSERVICEBUILDER_H
#define DEFAULTMODELSSERVICEBUILDER_H

#include "abstractmodelsservicebuilder.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"
#include "imodelsservicebuilder.h"
#include "localmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iplayermodel.h"
#include "assembleplayerindexesfromjson.h"
#include "assemblejsonfromdartspointindexes.h"
#include "jsonarrayfromplayernamesandids.h"
#include "assemblejsonfromdartspoints.h"
#include "assemblejsonfromordereddartspointmodels.h"
#include "assembledartstournamentmodelfromjson.h"
#include "assemblejsondartstournamentmodels.h"
#include "ibinaryservice.h"
#include "assemblejsonfromplayeridandname.h"

class DefaultModelsServiceBuilder :
        public AbstractModelsServiceBuilder<AbstractApplicationInterface,AbstractModelsService>
{
public:
    static DefaultModelsServiceBuilder* createInstance();
    AbstractModelsService *buildLocalModelsServiceWithJsonDb(AbstractApplicationInterface *applicationInterface) override;
    DefaultModelsServiceBuilder* setModelsTournamentServiceBuilder(IModelsServiceBuilder<IDartsModelsService>* builder);
    DefaultModelsServiceBuilder* setPlayerServiceBuilder(IModelsServiceBuilder<IPlayerModelsService<IPlayerModel<QUuid, QString> > > *playerServiceBuilder);
private:
    IModelsServiceBuilder<IDartsModelsService>* _tournamentServiceBuilder;
    IModelsServiceBuilder<IPlayerModelsService<IPlayerModel<QUuid,QString>>>* _playerServiceBuilder;
};

#endif // DEFAULTMODELSSERVICEBUILDER_H
