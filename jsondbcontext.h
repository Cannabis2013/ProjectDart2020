#ifndef LOCALTOURNAMENTMODELDB_H
#define LOCALTOURNAMENTMODELDB_H

#include <quuid.h>
#include "imodelsdbcontext.h"
#include "persistenceinterface.h"
#include "abstractpersistence.h"
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include "imodel.h"
#include "abstractjsonpersistence.h"
#include "playermodel.h"
/*
 * Include json assembler/extractor service
 */
#include "idartsinputassembler.h"
#include "idartstournamentsjsonassemblerservice.h"
#include "iplayerjsonassemblerservice.h"
#include "idartsinputjsonextractor.h"
#include "idartstournamentjsonextractorservice.h"
#include "idartstournamentjsonextractorservice.h"
#include "iplayerjsonextractorservice.h"

class JsonDbContext :
        public IModelsDbContext,
        public AbstractJSONPersistence
{
public:
    // Public types
    typedef QVector<const IModel<QUuid>*> modelsList;
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };
    JsonDbContext():
        _fileName("Models")
    {
        fetchModels();
    }
    JsonDbContext(const QString& fileName):
        _fileName(fileName)
    {
        fetchModels();
    }
    // PersistenceInterface interface
    void fetchModels() override;
    void saveState() override;
    // ImodelsDBContext interface
    void addTournament(const IModel<QUuid> *model) override;
    const IModel<QUuid> *dartsTournamentModelFromIndex(const int &index) override;
    virtual const IModel<QUuid> *dartsTournamentModelFromIndex(const QUuid &id) override;
    QVector<const IModel<QUuid> *> dartsTournaments() override;
    void removeDartsTournamentModelFromId(const QUuid &id) override;
    void removeDartsTournamentModelFromId(const int &index) override;
    int indexOfTournament(const IModel<QUuid>* model) override;
    void replaceTournament(const int& index, const IModel<QUuid> *tournament) override;
    void addScoreModel(const IModel<QUuid>* model) override;
    const IModel<QUuid>* scoreModel(const int &index) override;
    QVector<const IModel<QUuid> *> dartsPointModels() override;
    virtual int indexOfScoreModel(const IModel<QUuid>* score) override;
    virtual void replaceScoreModel(const int &index, const IModel<QUuid>* score) override;
    virtual void removeScoreModel(const int &index) override;
    virtual void addPlayerModel(const IModel<QUuid>* player) override;
    virtual const IModel<QUuid> *playerModel(const int &index) override;
    virtual QVector<const IModel<QUuid> *> playerModels() override;
    virtual void removePlayerModel(const QUuid &id) override;
    virtual void removePlayerModel(const int &index) override;
    virtual int indexOfPlayerModel(const IModel<QUuid> *player) override;
    virtual void replacePlayerModel(const int &index, const IModel<QUuid> *player) override;
private:
    void addModel(const IModel<QUuid>& m);
    /*
     * Extract models from JSON
     */
    QJsonArray assembleDartsTournamentsJsonArray();
    QJsonArray assembleDartsPointsJSONArray();
    QJsonArray assemblePlayersJSONArray();
    /*
     * Get models from JSON
     */
    void extractDartsTournamentModelsFromJSON(const QJsonArray &arr);
    void extractScoreModelsFromJSON(const QJsonArray &arr);
    void extractPlayerModelsFromJSON(const QJsonArray &arr);

    const QString _fileName;

    /*
     * Json extractor services
     */
    IDartsInputJsonExtractor<QJsonValue,IModel<QUuid>,IModel<QUuid>>* _dartsInputExtractor;
    IDartsTournamentJsonExtractorService<QJsonArray,const QVector<const IModel<QUuid>*>>* _dartsTournamentJsoNExstractorService;
    IPlayerJsonExtractorService<QJsonArray,QVector<const IModel<QUuid>*>>* _playerJsonExtractorService;
    /*
     * Json assembler services
     */
    IDartsInputAssembler<QJsonArray,modelsList>* _dartsInputAssembler;
    IDartsTournamentsJsonAssemblerService<QJsonArray,QVector<const IModel<QUuid>*>>* _dartsTournamentAssembler;
    IPlayerJsonAssemblerService<QJsonArray,QVector<const IModel<QUuid>*>>* _playerModelsAssemblerService;
    /*
     * Models storage containers
     */
    QVector<const IModel<QUuid>*> _dartsTournamentModels;
    QVector<const IModel<QUuid>*> _dartsPointModels;


    QVector<const IModel<QUuid>*> _playerModels;
};
#endif // LOCALTOURNAMENTMODELDB_H
