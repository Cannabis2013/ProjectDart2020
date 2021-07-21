#ifndef PLAYERMODELSJSONDB_H
#define PLAYERMODELSJSONDB_H

#include <quuid.h>
#include "idbservice.h"
#include "abstractpersistence.h"
#include "jsonpersistence.h"
#include "playermodel.h"
#include "icreateplayersfromjson.h"
#include "icreatejsonfromplayermodels.h"
namespace ModelsContext {
    class PlayerModelsJsonDb :
            public IDbService,
            public JSONPersistence
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
        PlayerModelsJsonDb(const QString &fileName):
            _fileName(fileName)
        {}
        virtual void add(const IModel<QUuid> *player) override;
        virtual const IModel<QUuid> *model(const int &index) const override;
        virtual QVector<const IModel<QUuid>*> models() const override;
        virtual bool remove(const int &index) override;
        virtual int indexOf(const IModel<QUuid> *player) const override;
        virtual void replace(const int &index, const IModel<QUuid> *player) override;
    protected:
        void fetchModels() override;
        void saveState() override;
        ICreatePlayersFromJson *_createPlayerModels;
        ICreateJsonFromPlayerModels *_createJsonFromModels;
    private:
        const QString _fileName = "playerModels";
        QVector<const IModel<QUuid>*> _playerModels;
    };
}

#endif // LOCALTOURNAMENTMODELDB_H
