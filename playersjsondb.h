#ifndef LOCALTOURNAMENTMODELDB_H
#define LOCALTOURNAMENTMODELDB_H

#include <quuid.h>
#include "iplayermodelsdb.h"
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
#include "idartstournamentjsonextractorservice.h"
#include "idartstournamentjsonextractorservice.h"
#include "iplayerjsonextractorservice.h"

namespace DartsModelsContext {
    class PlayersJsonDb :
            public IPlayerModelsDb,
            public AbstractJSONPersistence
    {
    public:
        // Public types
        typedef QVector<const IModel<QUuid,QByteArray>*> modelsList;
        enum GameModes {
            FirstToPost = 0x1,
            RoundLimit =0x2,
            Circular = 0x3,
            Cricket = 0x4
        };
        typedef  IUnaryService<const QJsonArray&,QVector<const IPlayerModel*>> JsonExtractor;
        typedef IUnaryService<const QVector<const IPlayerModel*>&,QJsonArray> JsonAssembler;
        static PlayersJsonDb* createInstance(JsonExtractor* jsonExtractorService,
                                             JsonAssembler* jsonAssemblerService);
        // PersistenceInterface interface
        void fetchModels() override;
        void saveState() override;
        virtual void addPlayerModel(const IPlayerModel *player) override;
        virtual const IPlayerModel *playerModel(const int &index) override;
        virtual QVector<const IPlayerModel *> playerModels() override;
        virtual void removePlayerModel(const QUuid &id) override;
        virtual void removePlayerModel(const int &index) override;
        virtual int indexOfPlayerModel(const IPlayerModel *player) override;
        virtual void replacePlayerModel(const int &index, const IPlayerModel *player) override;

        PlayersJsonDb *setPlayerModelsAssemblerService(IUnaryService<const QVector<const IPlayerModel *> &, QJsonArray> *playerModelsAssemblerService);
        PlayersJsonDb *setPlayerJsonExtractorService(IUnaryService<const QJsonArray &, QVector<const IPlayerModel *> > *playerJsonExtractorService);

    private:
        const QString _fileName = "playerModels";
        // Json services
        IUnaryService<const QJsonArray&,QVector<const IPlayerModel*>>* _playerJsonExtractorService;
        IUnaryService<const QVector<const IPlayerModel*>&,QJsonArray>* _playerModelsAssemblerService;
        /*
         * Models storage containers
         */
        QVector<const IPlayerModel*> _playerModels;
    };
}

#endif // LOCALTOURNAMENTMODELDB_H
