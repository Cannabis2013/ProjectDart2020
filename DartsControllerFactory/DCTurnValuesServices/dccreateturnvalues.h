#ifndef DCCREATETURNVALUES_H
#define DCCREATETURNVALUES_H
#include "DCTurnValuesSLAs/idccreateturnvalues.h"

class IDCFinishBuilder;
class DCInput;
template<typename T,typename U>
class IDCPlayerManager;
class QString;
struct DCPlayer;
template<typename T,typename U> class IDCIndexController;
struct DCMeta;
struct DCIndex;
class DCServices;
class DCCreateTurnValues : public IDCCreateTurnValues
{
public:
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    DCCreateTurnValues(DCServices *services);
    DCTurnValues create() const override;
private:
    DCTurnValues turnValues(const DCIndex &index, const DCPlayer &player, const QString &finish) const;
    IndexController *_indexController;
    PlayerManager *_playerManager;
    IDCFinishBuilder *_createFinishes;
};
#endif // ASSEMBLEDARTSSCORETURNVALUES_H
