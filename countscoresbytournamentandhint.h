#ifndef COUNTSCORESBYTOURNAMENTANDHINT_H
#define COUNTSCORESBYTOURNAMENTANDHINT_H

#include <quuid.h>
#include "idartsscoredb.h"
#include "iternaryservice.h"

class CountScoresByTournamentAndHint :
        public ITernaryService<const QUuid&,const int&, const IDartsScoreDb*,int>
{
public:
    int service(const QUuid& tournamentId,const int& hint, const IDartsScoreDb* dbService) override
    {
        auto models = dbService->dartsScoreModels();
        auto count = 0;
        for (const auto& model : models) {
            if(model->tournamentId() != tournamentId)
                continue;
            else if(model->hint() == hint)
                count++;
        }
        return count;
    }
};

#endif // COUNTSCORESBYTOURNAMENTANDHINT_H
