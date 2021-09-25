#ifndef JSONPLAYERSDBCONTEXT_H
#define JSONPLAYERSDBCONTEXT_H

#include <quuid.h>
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "PlayerModelsContext/Services/playermodel.h"
#include "ModelsContext/MCJsonSLAs/modelsdbjsonslas.h"
#include "modelsdbioservices.h"

namespace PlayersContext {
    class JsonPlayersDbContext :
            public IModelsDbContext,
            protected ModelsDbJsonSLAs,
            protected ModelsDbIOSLAs
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
        virtual void add(const IModel<QUuid> *player) override;
        virtual const IModel<QUuid> *model(const int &index) const override;
        virtual QVector<const IModel<QUuid>*> models() const override;
        virtual bool remove(const int &index) override;
        virtual int indexOf(const IModel<QUuid> *player) const override;
        virtual void replace(const int &index, const IModel<QUuid> *player) override;
    protected:
        JsonPlayersDbContext()
        {}
        void fetchModels() override;
        void saveState() override;
    private:
        QVector<const IModel<QUuid>*> _playerModels;
    };
}

#endif // LOCALTOURNAMENTMODELDB_H
