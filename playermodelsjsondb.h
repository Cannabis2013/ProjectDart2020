#ifndef PLAYERMODELSJSONDB_H
#define PLAYERMODELSJSONDB_H

#include <quuid.h>
#include "iplayermodelsdb.h"
#include "abstractpersistence.h"
#include "jsonpersistence.h"
#include "playermodel.h"
#include "icreateplayersfromjson.h"
#include "icreatejsonfromplayermodels.h"
namespace DartsModelsContext {
    class PlayerModelsJsonDb :
            public IPlayerModelsDb,
            public JSONPersistence
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
        PlayerModelsJsonDb(const QString &fileName):
            _fileName(fileName)
        {}
        virtual void add(const IPlayerModel *player) override;
        virtual const IPlayerModel *model(const int &index) const override;
        virtual QVector<const IPlayerModel *> models() const override;
        virtual bool remove(const int &index) override;
        virtual int indexOf(const IPlayerModel *player) const override;
        virtual void replace(const int &index, const IPlayerModel *player) override;
    protected:
        void fetchModels() override;
        void saveState() override;
        ICreatePlayersFromJson *_createPlayerModels;
        ICreateJsonFromPlayerModels *_createJsonFromModels;
    private:
        const QString _fileName = "playerModels";
        QVector<const IPlayerModel*> _playerModels;
    };
}

#endif // LOCALTOURNAMENTMODELDB_H
