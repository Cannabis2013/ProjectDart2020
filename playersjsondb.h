#ifndef LOCALTOURNAMENTMODELDB_H
#define LOCALTOURNAMENTMODELDB_H

#include <quuid.h>
#include "imodelsdbcontext.h"
#include "ipersistence.h"
#include "abstractpersistence.h"
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include "imodel.h"
#include "abstractjsonpersistence.h"
#include "playermodel.h"
#include "iunaryservice.h"
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

class PlayersJsonDb :
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
    typedef  IUnaryService<const QJsonArray&,QVector<const IPlayerModel<QUuid,QString>*>> JsonExtractor;
    typedef IUnaryService<const QVector<const IPlayerModel<QUuid,QString>*>&,QJsonArray> JsonAssembler;
    static PlayersJsonDb* createInstance(JsonExtractor* jsonExtractorService,
                                         JsonAssembler* jsonAssemblerService);
    // PersistenceInterface interface
    void fetchModels() override;
    void saveState() override;
    virtual void addPlayerModel(const IPlayerModel<QUuid, QString> *player) override;
    virtual const IPlayerModel<QUuid,QString> *playerModel(const int &index) override;
    virtual QVector<const IPlayerModel<QUuid,QString> *> playerModels() override;
    virtual void removePlayerModel(const QUuid &id) override;
    virtual void removePlayerModel(const int &index) override;
    virtual int indexOfPlayerModel(const IPlayerModel<QUuid,QString> *player) override;
    virtual void replacePlayerModel(const int &index, const IPlayerModel<QUuid,QString> *player) override;

    PlayersJsonDb *setPlayerModelsAssemblerService(IUnaryService<const QVector<const IPlayerModel<QUuid, QString> *> &, QJsonArray> *playerModelsAssemblerService);
    PlayersJsonDb *setPlayerJsonExtractorService(IUnaryService<const QJsonArray &, QVector<const IPlayerModel<QUuid, QString> *> > *playerJsonExtractorService);

private:
    const QString _fileName = "playerModels";
    // Json services
    IUnaryService<const QJsonArray&,QVector<const IPlayerModel<QUuid,QString>*>>* _playerJsonExtractorService;
    IUnaryService<const QVector<const IPlayerModel<QUuid,QString>*>&,QJsonArray>* _playerModelsAssemblerService;
    /*
     * Models storage containers
     */
    QVector<const IPlayerModel<QUuid,QString>*> _playerModels;
};
#endif // LOCALTOURNAMENTMODELDB_H
