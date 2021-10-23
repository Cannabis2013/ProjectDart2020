#ifndef DARTSJSONMODELSCONTEXT_H
#define DARTSJSONMODELSCONTEXT_H

#include "DartsModelsContext/Services/dartsmodelscontext.h"
// Genereic models includes
#include "DartsModelsContext/DMCInputServices/removedartsinputsfromdb.h"
#include "FileOperationsContext/Services/readbytearray.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "DartsModelsContext/TournamentServices/dartsmetamodelbuilder.h"
// Input models includes
#include "DartsModelsContext/DMCInputServices/getdartsinputmodels.h"
#include "DartsModelsContext/DMCInputServices/sortdartsinputs.h"
#include "DartsModelsContext/DMCInputServices/sortdartsinputsbyindexes.h"
#include "DartsModelsContext/DMCInputServices/countdartsinputs.h"
#include "DartsModelsContext/DMCInputServices/getdartsinputfromdb.h"
#include "DartsModelsContext/DMCInputServices/dartsinputbuilder.h"
#include "DartsModelsContext/DMCInputServices/dartsinputsdbcontext.h"
#include "dartsinputjsonbuilder.h"
// Tournament indexes includes
#include "DartsModelsContext/IndexesDbServices/removedartsindexes.h"
#include "DartsModelsContext/IndexesDbServices/dartsindexesdbcontext.h"
#include "DartsModelsContext/IndexesServices/updatedartsindexes.h"
#include "DartsModelsContext/IndexesServices/dartsindexesjsonbuilder.h"
#include "DartsModelsContext/IndexesDbServices/dartsindexbuilder.h"
#include "DartsModelsContext/IndexesDbServices/getdartsindexesmodel.h"
#include "DartsModelsContext/IndexesServices/resetdartsindexes.h"
// Tournament models includes
#include "DartsModelsContext/TournamentServices/resetdartstournament.h"
#include "DartsModelsContext//TournamentsDbServices/dartsdbcontext.h"
#include "DartsModelsContext/TournamentServices/getdartstournamentfromdb.h"
#include "DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h"
#include "DartsModelsContext/TournamentServices/setdartsplayerdetails.h"
#include <DartsModelsContext/TournamentsDbServices/dartstournamentjsonbuilder.h>
#include <DartsModelsContext/TournamentServices/dartstournamentbuilder.h>

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
