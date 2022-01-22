#ifndef ITOURNAMENTREPAIR_H
#define ITOURNAMENTREPAIR_H
template<typename T>
class QVector;
class AbsPlaCtx;
class IDartsInput;
class IDartsTournament;
template<typename TModel>
class ITournamentRepair
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    virtual bool repair(Model *tournament,
                        const Models &inputs,
                        AbsPlaCtx *playersContext) const = 0;
};
#endif // ITOURNAMENTREPAIR_H
