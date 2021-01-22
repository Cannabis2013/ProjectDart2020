#ifndef LOCALTOURNAMENTMODELDB_H
#define LOCALTOURNAMENTMODELDB_H

#include <quuid.h>
#include <QMultiHash>
#include "imodelsdbcontext.h"
#include "tournamentmodelbuilder.h"

#include "persistenceinterface.h"
#include "abstractpersistence.h"

#include <qjsonobject.h>
#include <qjsonarray.h>

class LocalTournamentModelDB :
        public ImodelsDBContext<ModelInterface<QUuid>,QString>,
        public AbstractPersistence,
        public PersistenceInterface
{
public:
    /*
     * Public types
     */
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };
    LocalTournamentModelDB(const QString& orgName = "MH", const QString& appName = "Dart2020");
    ~LocalTournamentModelDB();
    const QStringList acceptedModelTypes = {"Tournament", "Round", "Set", "Score"};

    // IModelDBContext interface
    bool addModel(const QString &type, const ModelInterface<QUuid> *model) override;
    bool removeModel(const QString &type, const int &indexOfModel) override;
    bool replaceModel(const QString &type, const int &indexOfModel, const ModelInterface<QUuid> *newModel) override;
    const ModelInterface<QUuid> *model(const QString &type, const int &index) override;
    int indexOfModel(const QString &type, const ModelInterface<QUuid> *model) override;
    int countOfModels(const QString &type) override;
    QList<const ModelInterface<QUuid> *> models(const QString &type) override;

    // PersistenceInterface interface
    void read() override;
    void write() override;
private:
    QJsonArray assembleTournamentsJSONArray();
    QJsonObject assembleFTPTournamentJSONArray(const FTPTournament *tournamentModel);
    QJsonArray assembleScoresJSONArray();

    void extractTournamentModelsFromJSON(const QJsonArray &arr);
    void extractScoreModelsFromJSON(const QJsonArray &arr);

    QMultiHash<QString,const ModelInterface<QUuid>*> _models;
};
#endif // LOCALTOURNAMENTMODELDB_H
