#ifndef DARTSJSONMODELSCONTEXT_H
#define DARTSJSONMODELSCONTEXT_H
#include "DartsModelsContext/Services/dartsmodelscontext.h"
#include "DartsModelsContext/DMCInputServices/removedartsinputsfromdb.h"
#include "FileOperationsContext/Services/readbytearray.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "DartsModelsContext/TournamentServices/dartsmetamodelbuilder.h"
#include "DartsModelsContext/DMCInputServices/getdartsinputmodels.h"
#include "DartsModelsContext/DMCInputServices/sortdartsinputs.h"
#include "DartsModelsContext/DMCInputServices/sortdartsinputsbyindexes.h"
#include "DartsModelsContext/DMCInputServices/countdartsinputs.h"
#include "DartsModelsContext/DMCInputServices/getdartsinputfromdb.h"
#include "DartsModelsContext/DMCInputServices/dartsinputbuilder.h"
#include "DartsModelsContext/DMCInputServices/dartsinputsdbcontext.h"
#include "dartsinputjsonbuilder.h"
#include "DartsModelsContext/IndexesServices/updatedartsindexes.h"
#include "DartsModelsContext/IndexesDbServices/dartsindexbuilder.h"
#include "DartsModelsContext/IndexesServices/resetdartsindexes.h"
#include "DartsModelsContext/TournamentServices/resetdartstournament.h"
#include "DartsModelsContext//TournamentsDbServices/dartsdbcontext.h"
#include "DartsModelsContext/TournamentServices/getdartstournamentfromdb.h"
#include "DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h"
#include "DartsModelsContext/TournamentServices/setdartsplayerdetails.h"
#include <DartsModelsContext/TournamentsDbServices/dartstournamentjsonbuilder.h>
#include <DartsModelsContext/TournamentServices/dartstournamentbuilder.h>
#include "DartsModelsContext/TournamentServices/GetDartsTournamentIds.h"
class DartsJsonModelsContext : public DartsModelsContext
{
public:
    DartsJsonModelsContext();
private:
    void setModelUtilityServices();
    void setTournamentServices();
    void setIndexesServices();
    void setInputServices();
    void setInputDbUtilityServices();
    void fetchAll();
};
#endif // DARTSMODELSSERVICEWITHJSONDB_H
