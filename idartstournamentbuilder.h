#ifndef IDATAMODELBUILDER_H
#define IDATAMODELBUILDER_H

#include <qvector.h>

template<class TTournamentModel,
         class TUuid,
         class TString>
class IDartsTournamentBuilder
{
public:
    virtual TTournamentModel* buildFTPTournament(const TString &title,
                                                 const int& gameMode,
                                                 const int& keyPoint,
                                                 const int& terminalKeyCode,
                                                 const int& displayHint,
                                                 const int& inputHint,
                                                 const int& attempts,
                                                 const QVector<TUuid>& playerIds) = 0;
};

#endif // IDATAMODELBUILDER_H
