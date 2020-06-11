#ifndef IGAMECONTROLLER_H
#define IGAMECONTROLLER_H

/*
 *
 */

template<typename TUuid,class TString, class TDefaultLocalDataContext>
class IGameController
{
public:
    virtual TUuid currentTournament()  = 0;
    virtual void setCurrentTournament( TUuid &tournament) = 0;

    virtual TUuid start() = 0;
    virtual void stop() = 0 ;

    virtual int processInput(const int &point) = 0;

    virtual TString playerMessage()  = 0;

    virtual TUuid currentActivePlayer() = 0;
    virtual int currentRoundIndex() = 0;
    virtual int currentPlayerIndex() = 0;
    virtual int currentSetIndex() = 0;
    virtual int currentLegIndex() = 0;

    virtual int status()  = 0;

    virtual TString calculateThrowSuggestion()  = 0;

    virtual TUuid determinedWinner()  = 0;

    virtual TUuid undoTurn() = 0;
    virtual TUuid redoTurn() = 0;

    virtual int lastPlayerIndex()  = 0;
    virtual int playerIndex()  = 0;

    virtual void setDataContext(TDefaultLocalDataContext *dataContext) = 0;
    virtual TDefaultLocalDataContext *dataContext() = 0;
};

#endif // IGAMECONTROLLER_H
