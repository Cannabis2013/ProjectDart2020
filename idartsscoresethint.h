#ifndef IDARTSSCORESETHINT_H
#define IDARTSSCORESETHINT_H
#include "idartsscoreinput.h"
#include "idartsscoreindexes.h"
template<typename TDbModelsService>
class IDartsScoreSetHint
{
public:
    typedef TDbModelsService DbModelsService;
    typedef IPlayerInput PlayerInput;
    typedef QVector<const PlayerInput*> PlayerInputs;
    virtual void setDartsScoreHint(const PlayerInput* model,const int &hint, DbModelsService* dbService) = 0 ;
};
#endif // IDARTSSCOREMODELSSERVICE_H
