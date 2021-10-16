#ifndef IDARTSMETAMODELBUILDER_H
#define IDARTSMETAMODELBUILDER_H

#include <quuid.h>
#include <QString>

struct DartsMetaModel
{
    QUuid playerId;
    QString playerName;
    QUuid tournamentId;
};

class IDartsMetaModelBuilder
{
public:
    virtual DartsMetaModel buildMetaModel(const QByteArray &json) const = 0;
};
#endif // IDARTSMETAMODELBUILDER_H
