#ifndef DARTSTOURNAMENTJSONEXTRACTOR_H
#define DARTSTOURNAMENTJSONEXTRACTOR_H

#include "iunaryservice.h"

#include <qjsonarray.h>
#include <qjsonobject.h>
#include <dartstournament.h>
#include <qvector.h>


namespace JsonExtractorContext {
    typedef QVector<const IDartsTournament<QUuid,QString>*> DartsTournaments;
}

class DartsTournamentJsonExtractor :
        public IUnaryService<const QJsonArray&,QVector<const IModel<QUuid>*>>
{
public:
    QVector<const IModel<QUuid>*> service(const QJsonArray& arr) override;
};

#endif // DARTSTOURNAMENTJSONEXTRACTOR_H
