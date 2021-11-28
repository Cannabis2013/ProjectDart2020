#ifndef DARTSMODELSSLAS_H
#define DARTSMODELSSLAS_H
#include "DartsModelsContext/InputSLAs/dartsiptslas.h"
#include "DartsModelsContext/TournamentsSLAs/dartsslas.h"
#include "DartsModelsContext/InputsDbSLAs/DartsiptDbSLAs.h"
#include "DartsModelsContext/TournamentsDbSLAs/dartsdbslas.h"
#include "DartsModelsContext/IndexesSLAs/dartsindexslas.h"
class DartsCtxSLAs : public DartsSLAs,      public DartsIptSLAs,
                     public DartsiptDbSLAs, public DartsIndexSLAs,
                     public DartsDbSLAs
{};
#endif // DARTSMODELSSLAS_H
