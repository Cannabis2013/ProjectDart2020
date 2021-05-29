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
#include "assemblejsonbasictournamentvaluesfrommodel.h"
#include "assemblejsondartstournamentmodels.h"
#include "ibinaryservice.h"
#include "assemblejsonfromplayeridandname.h"
#include "assemblejsonbasictournamentvalues.h"
#include "gettournamentindexesfromjson.h"
#include "getdeleteplayerindexfromjson.h"
#include "assembledartspointmodelfromjson.h"
#include "assembleplayermodelfromjson.h"
#include "assignplayeridstodartstournamentmodel.h"
#include "addplayernametodartsinputmodel.h"
#include "idartsjsonservice.h"
#include "addplayernametodartsinputmodel.h"
#include "dartstournamentbuilder.h"


class DefaultModelsServiceBuilder :
        public AbstractModelsServiceBuilder<AbstractModelsService>
{
public:
    static DefaultModelsServiceBuilder* createInstance();
    AbstractModelsService *buildLocalModelsServiceWithJsonDb() override;
    DefaultModelsServiceBuilder* setModelsTournamentServiceBuilder(IModelsServiceBuilder<IDartsModelsService>* builder);
    DefaultModelsServiceBuilder* setPlayerServiceBuilder(IModelsServiceBuilder<IPlayerModelsService> *playerServiceBuilder);
    DefaultModelsServiceBuilder* setDartsJSonServiceBuilder(IModelsServiceBuilder<IDartsJsonService> *dartsJSonServiceBuilder);

private:
    IModelsServiceBuilder<IDartsJsonService>* _dartsJSonServiceBuilder;
    IModelsServiceBuilder<IDartsModelsService>* _localDartsTournamentServiceBuilder;
    IModelsServiceBuilder<IPlayerModelsService>* _playerServiceBuilder;
};

#endif // DEFAULTMODELSSERVICEBUILDER_H
