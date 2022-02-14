#ifndef DCROUTINES_H
#define DCROUTINES_H
#include "Routines/idcaddtomdsctx.h"
#include "idcresetservices.h"
#include "idcredoturn.h"
#include "idcundoturn.h"
#include "idccreatewinnerjson.h"
#include "Routines/idcinitialize.h"
#include "DCInputSLAs/idcinputevaluator.h"
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
    void setRedoTurn(IDCRedoTurn *newRedoTurn) {_redoTurn = newRedoTurn;}
    IDCInitialize *initializer() const {return _loader;}
    void setInitializer(IDCInitialize *service) {_loader = service;}
    IDCCreateWinnerJson *createWinnerReport() const {return _createWinnerReport;}
    void setCreateWinnerReport(IDCCreateWinnerJson *newCreateWinnerReport) {_createWinnerReport = newCreateWinnerReport;}
private:
    IDCInitialize *_loader;
    IDCAddToMdsCtx *_addToModelsCtx;
    IDCResetServices *_resetServices;
    IDCUndoTurn *_undoTurn;
    IDCRedoTurn *_redoTurn;
    IDCCreateWinnerJson *_createWinnerReport;
};
#endif // DCROUTINES_H
