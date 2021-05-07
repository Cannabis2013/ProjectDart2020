#ifndef DEFAULTMODELSSERVICEBUILDER_H
#define DEFAULTMODELSSERVICEBUILDER_H

#include "abstractmodelsservicebuilder.h"
#include "abstractmodelsservice.h"
#include "imodelsservicebuilder.h"
#include "localmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iplayermodel.h"
#include "getplayerindexesfromjson.h"
#include "assemblejsonfromdartspointindexes.h"
#include "jsonarrayfromplayernamesandids.h"
#include "assemblejsonfromdartspoints.h"
#include "assemblejsonfromordereddartspointmodels.h"
#include "assembledartstournamentmodelfromjson.h"
#include "assemblejsondartstournamentmodels.h"
#include "ibinaryservice.h"
#include "assemblejsonfromplayeridandname.h"
#include "assemblejsonfromdartstournamentmodel.h"
#include "gettournamentindexesfromjson.h"
#include "getdeleteplayerindexfromjson.h"
#include "assembledartspointmodelfromjson.h"

class DefaultModelsServiceBuilder :
        public AbstractModelsServiceBuilder<AbstractModelsService>
{
public:
    static DefaultModelsServiceBuilder* createInstance();
    AbstractModelsService *buildLocalModelsServiceWithJsonDb() override;
    DefaultModelsServiceBuilder* setModelsTournamentServiceBuilder(IModelsServiceBuilder<IDartsModelsService>* builder);
    DefaultModelsServiceBuilder* setPlayerServiceBuilder(IModelsServiceBuilder<IPlayerModelsService<IPlayerModel<QUuid, QString> > > *playerServiceBuilder);
private:
    IModelsServiceBuilder<IDartsModelsService>* _localDartsTournamentServiceBuilder;
    IModelsServiceBuilder<IPlayerModelsService<IPlayerModel<QUuid,QString>>>* _playerServiceBuilder;
};

#endif // DEFAULTMODELSSERVICEBUILDER_H
