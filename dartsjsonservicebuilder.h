#ifndef DARTSJSONSERVICEBUILDER_H
#define DARTSJSONSERVICEBUILDER_H

#include "dartsjsonservice.h"
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
#include "addplayernametodartsinputmodel.h"
#include "assembledartsscoremodelfromjson.h"
#include "assemblejsonfromdartsmultiattemptscores.h"
#include "assemblejsonbydartsscoreindexes.h"
#include "getwinneridbyjson.h"
#include "gettournamentidbyjson.h"
#include "addwinnernametotournamentjson.h"
#include "idartsjsonservicebuilder.h"
#include "dartspointsjsonservice.h"
#include "dartsscorejsonservice.h"

namespace DartsModelsContext {
    class DartsJsonServiceBuilder :
            public IDartsJsonServiceBuilder
    {

        // IDartsJsonServiceBuilder interface
    public:
        virtual IDartsJsonService *buildDartsJsonService() const override;
        virtual PointsJsonService *buildDartsPointsJsonService() const override;
        virtual ScoreJsonService *buildDartsScoreJsonService() const override;
    };
}

#endif // DARTSJSONSERVICEBUILDER_H
