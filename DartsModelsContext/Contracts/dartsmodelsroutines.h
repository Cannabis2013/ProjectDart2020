#ifndef DARTSMODELSROUTINES_H
#define DARTSMODELSROUTINES_H

#include <DartsModelsContext/Contracts/Routines/IDartsAddTournament.h>
#include <DartsModelsContext/Contracts/Routines/IDartsHideInput.h>
#include <DartsModelsContext/Contracts/Routines/IDartsSetWinner.h>
#include <DartsModelsContext/Contracts/Routines/idartsaddinputtodb.h>
#include <DartsModelsContext/Contracts/Routines/idartsinputstojson.h>
#include <DartsModelsContext/Contracts/Routines/idartsinputtojson.h>
#include <DartsModelsContext/Contracts/Routines/idartsremovetournaments.h>
#include <DartsModelsContext/Contracts/Routines/idartsresettournament.h>
#include <DartsModelsContext/Contracts/Routines/idartsrevealinput.h>
#include <DartsModelsContext/Contracts/Routines/igettournamentasjson.h>
#include <DartsModelsContext/Contracts/Routines/igettournamentsasjson.h>
#include <DartsModelsContext/Contracts/Routines/itournamentrepair.h>

template<typename T> class IModel;

class DartsModelsRoutines
{
public:
        typedef IModel<QUuid> Model;
        typedef IDartsInputsToJson<Model> InputsJsonBuilder;
        typedef IDartsHideInput<Model> HidePlayerInput;
        typedef IDartsRevealInput<Model> DisplayPlayerInput;
        typedef IDartsInputToJson<Model> InputToJson;
        typedef IDartsSetWinner<Model> SetTournamentWinner;
        typedef IGetTournamentAsJson<Model> GetTournamentAsJson;
        typedef ITournamentRepair<Model> RepairTournament;
        IDartsAddTournament *addTournamentToDb() const {return _addTournament;}
        void setAddTournamentToDb(IDartsAddTournament *routine) {_addTournament = routine;}
        IDartsRemoveTournaments *removeTournaments() const {return _removeTournaments;}
        void setRemoveTournaments(IDartsRemoveTournaments *routine) {_removeTournaments = routine;}
        IDartsResetTournament *resetDarts() const {return _resetTournament;}
        void setResetTournament(IDartsResetTournament *routine) {_resetTournament = routine;}
        InputsJsonBuilder *inputsToJson() const {return _createJsonFromInputs;}
        void setCreateJsonFromInputs(InputsJsonBuilder *routine) {_createJsonFromInputs = routine;}
        HidePlayerInput *hidePlayerInput() const {return _setInputHint;}
        void setHidePlayerInput(HidePlayerInput *routine) {_setInputHint = routine;}
        DisplayPlayerInput *displayPlayerInput() const {return _displayPlayerInput;}
        void setDisplayPlayerInput(DisplayPlayerInput *routine) {_displayPlayerInput = routine;}
        IDartsAddInputToDb *addInputToDb() const {return _addInputToDb;}
        void setAddInputToDb(IDartsAddInputToDb *routine) {_addInputToDb = routine;}
        InputToJson *inputToJson() const {return _inputToJson;}
        void setInputToJson(InputToJson *routine) {_inputToJson = routine;}
        SetTournamentWinner *setTnmWinner() const {return _setWinner;}
        void setSetWinner(SetTournamentWinner *routine) {_setWinner = routine;}
        GetTournamentAsJson *getTournamentAsJson() const {return _getTournamentAsJson;}
        void setGetTournamentAsJson(GetTournamentAsJson *routine) {_getTournamentAsJson = routine;}
        IGetTournamentsAsJson *getTournamentsAsJson() const {return _getTournamentsAsJson;}
        void setGetTournamentsAsJson(IGetTournamentsAsJson *routine) {_getTournamentsAsJson = routine;}
        RepairTournament *tournamentRepair() const {return _tournamentRepair;}
        void setTournamentRepair(RepairTournament *service) {_tournamentRepair = service;}
private:
        IDartsAddTournament *_addTournament;
        IDartsRemoveTournaments *_removeTournaments;
        IDartsResetTournament *_resetTournament;
        InputsJsonBuilder *_createJsonFromInputs;
        HidePlayerInput *_setInputHint;
        DisplayPlayerInput *_displayPlayerInput;
        IDartsAddInputToDb *_addInputToDb;
        InputToJson *_inputToJson;
        SetTournamentWinner *_setWinner;
        GetTournamentAsJson *_getTournamentAsJson;
        IGetTournamentsAsJson *_getTournamentsAsJson;
        RepairTournament *_tournamentRepair;
};
#endif // DARTSMODELSROUTINES_H