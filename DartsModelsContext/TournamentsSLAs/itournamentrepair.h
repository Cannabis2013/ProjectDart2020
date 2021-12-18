#ifndef ITOURNAMENTREPAIR_H
#define ITOURNAMENTREPAIR_H
template<typename T>
class QVector;
class AbsPlaCtx;
class AbstractDartsInput;
class IDartsTournament;
class ITournamentRepair
{
public:
    virtual bool repair(IDartsTournament *tournament,
                        const QVector<AbstractDartsInput*> &inputs,
                        AbsPlaCtx *playersContext) const = 0;
};
#endif // ITOURNAMENTREPAIR_H
