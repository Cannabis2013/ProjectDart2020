#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H

#include <quuid.h>
#include <qvector.h>
#include <ModelsContext/MCModelsSLAs/imodel.h>

class ITournamentJsonBuilder
{
public:
    virtual QByteArray tournamentJson(IModel<QUuid> *model) const = 0;
    virtual QByteArray tournamentsjson(const QVector<IModel<QUuid>*>& models) const = 0;
    virtual QByteArray assignedPlayersJson(IModel<QUuid> *model) const = 0;
    virtual QByteArray winnerDetailsJson(IModel<QUuid> *model) const = 0;
};

#endif // ICREATEJSONFROMDARTSINPUT_H
