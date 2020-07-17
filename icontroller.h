#ifndef IGAMECONTROLLER_H
#define IGAMECONTROLLER_H

template<typename TUuid,class TString>
class IController
{
public:
    virtual TUuid currentTournamentID()  = 0;
    virtual TString playerMessage()  = 0;

    virtual TUuid currentActivePlayer() = 0;
    virtual int currentRoundIndex() = 0;
    virtual int currentPlayerIndex() = 0;
    virtual int currentSetIndex() = 0;
    virtual int currentLegIndex() = 0;

    virtual int status()  = 0;

    virtual TString calculateThrowSuggestion(const int &score)  = 0;

    virtual TUuid determinedWinner()  = 0;

    virtual TUuid undoTurn() = 0;
    virtual TUuid redoTurn() = 0;

    virtual bool canUndoTurn() = 0;
    virtual bool canRedoTurn() = 0;

    virtual int lastPlayerIndex()  = 0;
    virtual int playerIndex()  = 0;
};

#endif // IGAMECONTROLLER_H
