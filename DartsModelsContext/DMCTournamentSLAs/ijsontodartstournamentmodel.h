#ifndef IJSONTODARTSTOURNAMENTMODEL_H
#define IJSONTODARTSTOURNAMENTMODEL_H

#include "DartsModelsContext/DMCTournamentSLAs/abstractdartstournament.h"
#include "idartstournamentextractor.h"

class IJsonToDartsTournamentModel
{
public:
    virtual const AbstractDartsTournament *create(const QByteArray &json,
                                                  const IDartsTournamentExtractor *extractor) const = 0;
};

#endif // IDARTSCREATETOURNAMENT_H
