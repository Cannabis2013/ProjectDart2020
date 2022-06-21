#ifndef DCINITIALIZE_H
#define DCINITIALIZE_H

#include <DartsController/Contracts/Routines/idcinitialize.h>

struct DCIndex;
class DCServices;
template<typename T,typename U> class IDCIndexController;
template<typename T> class IDCMetaConverter;
template<typename T> class IDCJsonToModel;
template<typename T> class IDCJsonToModels;
template<typename T> class IDCMetaManager;
template<typename T,typename U> class IDCPlayerManager;

class DCInitialize : public IDCInitialize
{
public:
        typedef IDCMetaManager<DCMeta> MetaManager;
        typedef IDCMetaConverter<DCMeta> MetaConverter;
        typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
        typedef IDCJsonToModel<DCInput> JsonToInput;
        typedef IDCJsonToModels<DCInput> JsonToInputs;
        typedef IDCJsonToModels<DCPlayer> JsonToPlayers;
        typedef IDCJsonToModel<DCPlayer> JsonToPlayer;
        typedef IDCIndexController<DCIndex,DCMeta> IndexController;
        DCInitialize(DCServices *services);
        int init(const QUuid &tournamentId) override;
private:
        void initMeta(const QUuid &tournamentID);
        void initPlayerDetails();
        void initPlayerScores();
        void initStatus();
        void updatePlayers(QVector<DCPlayer> &players, const int &remScore);
        JsonToInput *_jsonToInput;
        JsonToInputs *_jsonToInputs;
        PlayerManager *_playerManager;
        MetaManager *_metaManager;
        MetaConverter *_jsonToMeta;
        AbstractDartsContext *_modelsContext;
        JsonToPlayer *_jsonToPlayer;
        JsonToPlayers *_byteArrayToPlayers;
        IndexController *_indexController;
};
#endif // DCLOADMODELS_H
