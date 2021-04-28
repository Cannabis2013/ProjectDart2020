#ifndef IMODELDBCONTEXT_H
#define IMODELDBCONTEXT_H

#include <qvector.h>
#include <quuid.h>
#include "iplayermodel.h"
#include "persistenceinterface.h"

class IModelsDbContext : public PersistenceInterface
{
public:
    // Public types
    virtual ~IModelsDbContext() = default;
    // Tournament section
    virtual void addTournament(const IModel<QUuid>* model) = 0;
    virtual const IModel<QUuid>* dartsTournamentModelFromIndex(const int&) = 0;
    virtual const IModel<QUuid>* dartsTournamentModelFromIndex(const QUuid&) = 0;
    virtual QVector<const IModel<QUuid>*> dartsTournaments() = 0;
    virtual void removeDartsTournamentModelFromId(const QUuid&) = 0;
    virtual void removeDartsTournamentModelFromId(const int&) = 0;
    virtual int indexOfTournament(const IModel<QUuid>*) = 0;
    virtual void replaceTournament(const int&, const IModel<QUuid>*) = 0;
    // Score section
    virtual void addScoreModel(const IModel<QUuid>* model) = 0;
    virtual const IModel<QUuid>* scoreModel(const int& index) = 0;
    virtual QVector<const IModel<QUuid>*> dartsPointModels() = 0;
    virtual void removeScoreModel(const int&) = 0;
    virtual int indexOfScoreModel(const IModel<QUuid>*) = 0;
    virtual void replaceScoreModel(const int&, const IModel<QUuid>*) = 0;
    // Player section
    virtual void addPlayerModel(const IModel<QUuid>*) = 0;
    virtual const IModel<QUuid>* playerModel(const int&) = 0;
    virtual QVector<const IModel<QUuid>*> playerModels() = 0;
    virtual void removePlayerModel(const QUuid&) = 0;
    virtual void removePlayerModel(const int&) = 0;
    virtual int indexOfPlayerModel(const IModel<QUuid>*) = 0;
    virtual void replacePlayerModel(const int&, const IModel<QUuid>*) = 0;
};

#endif // IMODELDBCONTEXT_H
