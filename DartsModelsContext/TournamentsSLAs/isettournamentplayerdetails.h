#ifndef ISETTOURNAMENTPLAYERDETAILS_H
#define ISETTOURNAMENTPLAYERDETAILS_H
template<typename T>
class QVector;
class IPlayer;
template<typename T>
class IModel;
class QUuid;
class ISetTournamentPlayerDetails
{
public:
    virtual void setDetails(IModel<QUuid> *tournament, const QVector<IPlayer*> &playerModels) const = 0;
};

#endif // IDARTSMODELMANIPULATOR_H
