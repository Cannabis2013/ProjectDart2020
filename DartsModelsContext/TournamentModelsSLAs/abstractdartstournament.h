#ifndef FTPTOURNAMENTMODELINTERFACE_H
#define FTPTOURNAMENTMODELINTERFACE_H
#include "DartTournamentsContext/DTCModelsServices/abstracttournament.h"
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class AbstractDartsTournament : public AbstractTournament,
                                public DartsIndex
{
public:
    virtual int initialRemaining() const = 0;
    virtual AbstractDartsTournament* setKeyPoint(const int &val) = 0;
    virtual int inputHint() const = 0;
    virtual AbstractDartsTournament* setInputMode(const int &inputMode) = 0;
};

#endif // FTPTOURNAMENTMODELINTERFACE_H
