#ifndef REMOVETOURNAMENTSFROMDB_H
#define REMOVETOURNAMENTSFROMDB_H

#include "iremovetournamentsfromdb.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

/*
 * Context responsibilities
 *  - Get and modify data values from data storage class containers
 *  - Build and persist data storage class containers by the help of appropriate services
 */

namespace DartsModelsContext{
    class RemoveTournamentsFromDb :
            public IRemoveTournamentsFromDb
    {
    public:
        virtual bool removeTournamentsByIndexes(const QVector<int> &indexes, IDartsTournamentDb *dbService) const override;
    };
}

#endif // TOURNAMENTMODELCONTEXT_H
