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
    PlayersJsonDb():
        _fileName("Models")
    {
        fetchModels();
    }
    PlayersJsonDb(const QString& fileName):
        _fileName(fileName)
    {
        fetchModels();
    }
    // PersistenceInterface interface
    void fetchModels() override;
    void saveState() override;
    virtual void addPlayerModel(const IModel<QUuid>* player) override;
    virtual const IModel<QUuid> *playerModel(const int &index) override;
    virtual QVector<const IModel<QUuid> *> playerModels() override;
    virtual void removePlayerModel(const QUuid &id) override;
    virtual void removePlayerModel(const int &index) override;
    virtual int indexOfPlayerModel(const IModel<QUuid> *player) override;
    virtual void replacePlayerModel(const int &index, const IModel<QUuid> *player) override;
private:
    void addModel(const IModel<QUuid>& m);

    const QString _fileName;

    /*
     * Json extractor services
     */
    IUnaryService<const QJsonArray&,QVector<const IModel<QUuid>*>>* _playerJsonExtractorService;
    /*
     * Json assembler services
     */
    IPlayerJsonAssemblerService<QJsonArray,QVector<const IModel<QUuid>*>>* _playerModelsAssemblerService;
    /*
     * Models storage containers
     */
    QVector<const IModel<QUuid>*> _playerModels;
};
#endif // LOCALTOURNAMENTMODELDB_H
