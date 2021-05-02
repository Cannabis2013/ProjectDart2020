#ifndef DARTSTOURNAMENTJSONEXTRACTOR_H
#define DARTSTOURNAMENTJSONEXTRACTOR_H

#include "idartstournamentjsonextractorservice.h"

#include <qjsonarray.h>
#include <qjsonobject.h>
#include <dartstournament.h>
#include <qvector.h>

namespace JsonExtractorContext {
    typedef QVector<const IDartsTournament<QUuid,QString>*> DartsTournaments;
}

class DartsTournamentJsonExtractor : public IDartsTournamentJsonExtractorService<
        QJsonArray,QVector<const IModel<QUuid>*>>
{
public:


    // IDartsTournamentJsonExtractorService interface
public:
    QVector<const IModel<QUuid>*> extractDartsTournamentFromJson(const QJsonArray& arr) override;
};

#endif // DARTSTOURNAMENTJSONEXTRACTOR_H
