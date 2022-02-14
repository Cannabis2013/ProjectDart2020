#ifndef DCROUTINES_H
#define DCROUTINES_H
#include "idcaddtomdsctx.h"
#include "idcresetservices.h"
#include "idcredoturn.h"
#include "idcundoturn.h"
#include "idccreatewinnerjson.h"
#include "idcgetturnvaluesasjson.h"
#include "idcgetscoresasjson.h"
#include "Routines/idcinitialize.h"
#include "Inputs/idcinputevaluator.h"
class DCRoutines
{
public:
    IDCAddToMdsCtx *addInputToModelsContext() const {return _addToModelsCtx;}
    void setUpdateModelsContext(IDCAddToMdsCtx *service) {_addToModelsCtx = service;}
    IDCResetServices *resetServices() const {return _resetServices;}
    void setResetServices(IDCResetServices *service) {_resetServices = service;}
    IDCUndoTurn *undoTurn() const {return _undoTurn;}
    void setUndoTurn(IDCUndoTurn *service) {_undoTurn = service;}
    IDCRedoTurn *redoTurn() const {return _redoTurn;}
    void setRedoTurn(IDCRedoTurn *service) {_redoTurn = service;}
    IDCInitialize *initializer() const {return _initialize;}
    void setInitializer(IDCInitialize *service) {_initialize = service;}
    IDCCreateWinnerJson *createWinnerReport() const {return _createWinnerReport;}
    void setCreateWinnerReport(IDCCreateWinnerJson *service) {_createWinnerReport = service;}
    IDCGetTurnValuesAsJson *turnValuesAsJson() const {return _getTurnValuesAsJson;}
    void setGetTurnValuesAsJson(IDCGetTurnValuesAsJson *service) {_getTurnValuesAsJson = service;}
    IDCGetScoresAsJson *getScoresAsJson() const {return _getPlayersAsJson;}
    void setGetScoresAsJson(IDCGetScoresAsJson *service) {_getPlayersAsJson = service;}
private:
    IDCInitialize *_initialize;
    IDCAddToMdsCtx *_addToModelsCtx;
    IDCResetServices *_resetServices;
    IDCUndoTurn *_undoTurn;
    IDCRedoTurn *_redoTurn;
    IDCCreateWinnerJson *_createWinnerReport;
    IDCGetTurnValuesAsJson *_getTurnValuesAsJson;
    IDCGetScoresAsJson *_getPlayersAsJson;
};
#endif // DCROUTINES_H
