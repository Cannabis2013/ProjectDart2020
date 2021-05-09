#ifndef DARTSJSONSERVICEBUILDER_H
#define DARTSJSONSERVICEBUILDER_H

#include "dartsmodelsjsonservice.h"
#include "imodelsservicebuilder.h"

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
#include "addplayernametopointjson.h"
#include "assemblejsonfromdartspointmodel.h"

class DartsJsonServiceBuilder :
        public IModelsServiceBuilder<IDartsJsonService>
{

    // IModelsServiceBuilder interface
public:
    IDartsJsonService *buildModelsService() const override;
};

#endif // DARTSJSONSERVICEBUILDER_H
