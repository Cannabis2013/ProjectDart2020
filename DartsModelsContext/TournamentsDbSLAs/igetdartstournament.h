#ifndef IGETDARTSTOURNAMENT_H
#define IGETDARTSTOURNAMENT_H

template<typename T>
class QVector;
class QUuid;
template<typename TModel>
class IGetDartsTournament
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    virtual  Model *get(const QUuid &tournamentId, const Models &dbService) const = 0;
};

#endif // IGETDARTSTOURNAMENTDATA_H
