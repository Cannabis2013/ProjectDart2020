#ifndef IGETDARTSINPUT_H
#define IGETDARTSINPUT_H
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IGetDartsInput
{
public:
    virtual AbstractDartsInput *get(const DartsMetaModel &meta, const IDartsIndex *index,
                                    const IModelsDbContext *dbContext) const = 0;
};
#endif // IGETDARTSINPUT_H
