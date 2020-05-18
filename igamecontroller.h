#ifndef IGAMECONTROLLER_H
#define IGAMECONTROLLER_H

/*
 *
 */

template<typename TUuid,class TString, class TDefaultLocalDataContext, class TPointManagerInterface>
class IGameController
{
public:
    virtual TUuid currentTournament() const = 0;
    virtual void setCurrentTournament(const TUuid &tournament) = 0;

    virtual TUuid start() = 0;
    virtual void stop() = 0 ;

    virtual int processInput(const int &point) = 0;

    virtual TString playerMessage() const = 0;

    virtual TUuid currentActivePlayer() const = 0;
    virtual int currentRoundIndex() const = 0;
    virtual int currentPlayerIndex() const = 0;
    virtual int currentLegIndex() const = 0;

    virtual int status() const = 0;

    virtual TString calculateThrowSuggestion() const = 0;

    virtual TUuid determinedWinner() const = 0;

    virtual TUuid undoTurn() = 0;
    virtual TUuid redoTurn() = 0;

    virtual int lastPlayerIndex() const = 0;
    virtual int playerIndex() const = 0;

    virtual void setDataContext(TDefaultLocalDataContext *dataContext) = 0;
    virtual TDefaultLocalDataContext *dataContext() = 0;

    virtual TPointManagerInterface *pointManager() const = 0;
    virtual IGameController* setPointManager(TPointManagerInterface *interface) = 0;
};

#endif // IGAMECONTROLLER_H
