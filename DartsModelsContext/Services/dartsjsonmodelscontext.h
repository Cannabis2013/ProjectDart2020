#ifndef DARTSJSONMODELSCONTEXT_H
#define DARTSJSONMODELSCONTEXT_H

#include "DartsModelsContext/Services/dartsmodelscontext.h"
// Genereic models includes
#include "DartsModelsContext/DMCInputServices/dmcremoveinputsfromdb.h"
#include "removemodelsfromdb.h"
// Input models includes
#include "DartsModelsContext/DMCInputServices/dartsinputsjsondb.h"
#include "DartsModelsContext/DMCInputServices/dmcsetinputhint.h"
#include "DartsModelsContext/DMCInputServices/dmcgetinputmodels.h"
#include "DartsModelsContext/DMCInputServices/dmcsortinputs.h"
#include "sortdartspointinputsbyindexes.h"
#include "DartsModelsContext/DMCInputServices/dmccountinputs.h"
#include "DartsModelsContext/DMCInputServices/dmcinputstojson.h"
#include "DartsModelsContext/DMCInputServices/dmcgetinputfromdb.h"
#include "DartsModelsContext/DMCIndexesServices/dmccreateindexes.h"
#include "DartsModelsContext/DMCIndexesServices/dmcindexestojson.h"
#include "DartsModelsContext/DMCInputServices/dmcinputtojson.h"
#include "PlayerModelsContext/Services/createplayermodels.h"
// Player models includes
#include "PlayerModelsContext/Services/getplayersfromdb.h"
#include "createjsonfromplayers.h"
#include "PlayerModelsContext/Services/createplayerfromjson.h"
#include "PlayerModelsContext/DbServices/jsonplayersdbcontext.h"
#include "PlayerModelsContext/DbServices/localplayersdbcontext.h"
// Tournament models includes
#include "DartsModelsContext/DMCTournamentServices/dartstournamentextractor.h"
#include "removemodelsfromdb.h"
#include "DartsModelsContext/DMCTournamentServices/adddetailstotournamentjson.h"
#include "DartTournamentsContext/DTCDbServices/tournamentsjsondb.h"
#include "DartsModelsContext/DMCTournamentServices/createdartstournamentfromjson.h"
#include "DartsModelsContext/DMCTournamentServices/dartstournamentjsonbuilder.h"
#include "DartsModelsContext/DMCDbServices/dartstournamentsjsondb.h"
#include "DartsModelsContext/DMCTournamentServices/getdartstournamentfromdb.h"
#include "DartsModelsContext/DMCTournamentServices/extractwinnerinfofromjson.h"
#include "DartsModelsContext/DMCTournamentServices/addplayerdetailstotournament.h"
#include "DartsModelsContext/DMCTournamentServices/dartscreatejsonmetadata.h"
#include "DartsModelsContext/DMCInputServices/dmccreateinput.h"
#include "DartsModelsContext/DMCTournamentServices/gettournamentwinner.h"
#include "DartsModelsContext/DMCTournamentServices/createjsonfromtournamentdetails.h"

class DartsJsonModelsContext : public DartsModelsContext
{
public:
    DartsJsonModelsContext();
private:
    void setModelUtilityServices();
    void setTournamentServices();
    void setPointInputServices();
    void setInputDbUtilityServices();
    void setModelsServices();
};

#endif // DARTSMODELSSERVICEWITHJSONDB_H
