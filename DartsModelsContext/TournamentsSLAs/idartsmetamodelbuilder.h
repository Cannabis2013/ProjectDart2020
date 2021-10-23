#ifndef IDARTSMETAMODELBUILDER_H
#define IDARTSMETAMODELBUILDER_H

#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"

class IDartsMetaModelBuilder
{
public:
    virtual DartsMetaModel buildMeta(const QByteArray &json) const = 0;
};
#endif // IDARTSMETAMODELBUILDER_H
