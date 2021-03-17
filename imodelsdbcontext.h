#ifndef IMODELDBCONTEXT_H
#define IMODELDBCONTEXT_H

#include <qvector.h>
#include <iftptournament.h>
#include <iscoremodel.h>
#include <quuid.h>
#include "iplayermodel.h"
#include "persistenceinterface.h"

namespace DbModels {
    typedef ITournament<QUuid,QVector<QUuid>,QString> TournamentInterface;
    typedef IScore<QUuid> ScoreInterface;
    typedef IFTPTournament<QUuid,QVector<QUuid>,QString> IFirstToPostModel;
    typedef IPlayerModel<QUuid,QString> PlayerInterface;
}

class ImodelsDBContext : public PersistenceInterface
{
public:
    // Public types

    virtual ~ImodelsDBContext() = default;
    // Tournament section
    virtual void addTournament(DbModels::TournamentInterface* model) = 0;
    virtual const DbModels::TournamentInterface* tournamentModel(const int&) = 0;
    virtual const DbModels::TournamentInterface* tournamentModel(const QUuid&) = 0;
    virtual QVector<const DbModels::TournamentInterface*> tournaments() = 0;
    virtual void removeTournamentModel(const QUuid&) = 0;
    virtual void removeTournamentModel(const int&) = 0;
    virtual int indexOfTournament(const DbModels::TournamentInterface*) = 0;
    virtual void replaceTournament(const int&, const DbModels::TournamentInterface*) = 0;
    // Score section
    virtual void addScoreModel(const IScore<QUuid>* model) = 0;
    virtual const IScore<QUuid>* scoreModel(const int& index) = 0;
    virtual QVector<const IScore<QUuid>*> scoreModels() = 0;
    virtual void removeScoreModel(const int&) = 0;
    virtual int indexOfScoreModel(const IScore<QUuid>*) = 0;
    virtual void replaceScoreModel(const int&, const IScore<QUuid>*) = 0;
    // Player section
    virtual void addPlayerModel(const DbModels::PlayerInterface*) = 0;
    virtual const DbModels::PlayerInterface* playerModel(const int&) = 0;
    virtual QVector<const DbModels::PlayerInterface*> playerModels() = 0;
    virtual void removePlayerModel(const QUuid&) = 0;
    virtual void removePlayerModel(const int&) = 0;
    virtual int indexOfPlayerModel(const DbModels::PlayerInterface*) = 0;
    virtual void replacePlayerModel(const int&, const DbModels::PlayerInterface*) = 0;
};

#endif // IMODELDBCONTEXT_H
