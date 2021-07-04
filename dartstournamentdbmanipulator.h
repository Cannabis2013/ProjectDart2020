#ifndef DARTSTOURNAMENTDBMANIPULATOR_H
#define DARTSTOURNAMENTDBMANIPULATOR_H

#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>

#include "iplayermodelsdb.h"
#include "idartstournamentsdbmanipulator.h"
#include "jsonpersistence.h"
#include "idartstournamentdb.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "ipredicate.h"
#include "abstractdartsfilterpredicate.h"
#include "idartsinputsfilter.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

/*
 * Context responsibilities
 *  - Get and modify data values from data storage class containers
 *  - Build and persist data storage class containers by the help of appropriate services
 */

namespace DartsModelsContext{
    class DartsTournamentDbManipulator :
            public IDartsTournamentsDbManipulator
    {
    public:
        virtual Id addDartsTournamentToDb(const Tournament *tournament, DbService *dbService) override;
        virtual bool removeTournamentsByIndexes(const QVector<int> &indexes, DbService *dbService) const override;
    };
}

#endif // TOURNAMENTMODELCONTEXT_H
