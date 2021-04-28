#ifndef DARTSTOURNAMENTJSONEXTRACTOR_H
#define DARTSTOURNAMENTJSONEXTRACTOR_H

#include "idartstournamentjsonextractorservice.h"

#include <qjsonarray.h>
#include <qjsonobject.h>
#include <dartstournamentmodel.h>
#include <qvector.h>

namespace JsonExtractorContext {
    typedef QVector<const IDartsTournament<QUuid,QVector<QUuid>,QString>*> DartsTournaments;
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
