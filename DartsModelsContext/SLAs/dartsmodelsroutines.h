#ifndef DARTSMODELSROUTINES_H
#define DARTSMODELSROUTINES_H

#include "Routines/IDartsAddTournament.h"
#include "Routines/idartsremovetournaments.h"
#include "Routines/idartsresettournament.h"
#include "ModelSLAs/imodel.h"
#include "Routines/idartsinputstojson.h"
#include "Routines/IDartsHideInput.h"
#include "Routines/idartsrevealinput.h"
#include "Routines/idartsaddinputtodb.h"
#include "Routines/idartsinputtojson.h"

class DartsModelsRoutines
{
public:
    typedef IModel<QUuid> Model;
    typedef IDartsInputsToJson<Model> InputsJsonBuilder;
    typedef IDartsHideInput<Model> HidePlayerInput;
    typedef IDartsRevealInput<Model> DisplayPlayerInput;
    typedef IDartsInputToJson<Model> InputToJson;
    IDartsAddTournament *addTournamentToDb() const {return _addTournament;}
    void setAddTournamentToDb(IDartsAddTournament *service) {_addTournament = service;}
    IDartsRemoveTournaments *removeTournaments() const {return _removeTournaments;}
    void setRemoveTournaments(IDartsRemoveTournaments *service) {_removeTournaments = service;}
    IDartsResetTournament *resetDarts() const {return _resetTournament;}
    void setResetTournament(IDartsResetTournament *service) {_resetTournament = service;}
    InputsJsonBuilder *inputsToJson() const {return _createJsonFromInputs;}
    void setCreateJsonFromInputs(InputsJsonBuilder *service) {_createJsonFromInputs = service;}
    HidePlayerInput *hidePlayerInput() const {return _setInputHint;}
    void setHidePlayerInput(HidePlayerInput *service) {_setInputHint = service;}
    DisplayPlayerInput *displayPlayerInput() const {return _displayPlayerInput;}
    void setDisplayPlayerInput(DisplayPlayerInput *service) {_displayPlayerInput = service;}
    IDartsAddInputToDb *addInputToDb() const {return _addInputToDb;}
    void setAddInputToDb(IDartsAddInputToDb *service) {_addInputToDb = service;}
    InputToJson *inputToJson() const {return _inputToJson;}
    void setInputToJson(InputToJson *service) {_inputToJson = service;}
private:
    IDartsAddTournament *_addTournament;
    IDartsRemoveTournaments *_removeTournaments;
    IDartsResetTournament *_resetTournament;
    InputsJsonBuilder *_createJsonFromInputs;
    HidePlayerInput *_setInputHint;
    DisplayPlayerInput *_displayPlayerInput;
    IDartsAddInputToDb *_addInputToDb;
    InputToJson *_inputToJson;
};

#endif // DARTSMODELSROUTINES_H
