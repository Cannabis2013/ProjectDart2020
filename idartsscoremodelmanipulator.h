#ifndef IDARTSSCOREMODELMANIPULATOR_H
#define IDARTSSCOREMODELMANIPULATOR_H

#include "idartsscoreinput.h"
#include "idartsscoreindexes.h"
namespace DartsModelsContext {
    template<typename TDbModelsService>
    class IDartsScoreModelManipulator
    {
    public:
        typedef TDbModelsService DbModelsService;
        typedef IPlayerInput PlayerInput;
        typedef QVector<const PlayerInput*> PlayerInputs;
        virtual void setDartsScoreHint(const PlayerInput* model,const int &hint, DbModelsService* dbService) = 0 ;
    };
}

#endif // IDARTSSCOREMODELSSERVICE_H
