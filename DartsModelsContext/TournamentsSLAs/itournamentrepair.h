#ifndef ITOURNAMENTREPAIR_H
#define ITOURNAMENTREPAIR_H
class QUuid;
template<typename T>
class QVector;
template<typename TModel>
class ITournamentRepair
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    virtual bool repair(const QUuid &tournamentID) const = 0;
};
#endif // ITOURNAMENTREPAIR_H
