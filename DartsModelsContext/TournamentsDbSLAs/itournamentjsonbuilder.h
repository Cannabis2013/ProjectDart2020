#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H
#include <qjsonobject.h>
#include <quuid.h>
#include <qvector.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
class IDartsJsonBuilder
{
public:
    virtual QJsonObject tournamentJsonObject(IModel<QUuid> *model) const = 0;
    virtual QByteArray tournamentJson(IModel<QUuid> *model) const = 0;
    virtual QByteArray tournamentsjson(const QVector<IModel<QUuid>*>& models) const = 0;
    virtual QJsonArray assignedPlayersJson(IModel<QUuid> *model) const = 0;
    virtual QJsonObject winnerDetailsJson(IModel<QUuid> *model) const = 0;
};

#endif // ICREATEJSONFROMDARTSINPUT_H
