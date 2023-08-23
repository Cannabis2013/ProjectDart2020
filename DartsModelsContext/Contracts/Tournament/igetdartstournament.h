#ifndef IGETDARTSTOURNAMENT_H
#define IGETDARTSTOURNAMENT_H

#include <quuid.h>

template<typename TModel>

class IGetDartsTournament
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    virtual  Model *get(const QUuid &tournamentId, const Models &dbService) const = 0;
};

#endif // IGETDARTSTOURNAMENTDATA_H
