#ifndef IGETDARTSINPUT_H
#define IGETDARTSINPUT_H

#include "DartsModelsContext/InputsDbSLAs/iplayerinput.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "idartsinput.h"

class IGetDartsInput
{
public:
    virtual ModelsContext::IDartsInput *get(const DartsMetaModel &meta, const IDartsIndex *index,
                                            const IModelsDbContext *dbContext) const = 0;
};

#endif // IGETDARTSINPUT_H
