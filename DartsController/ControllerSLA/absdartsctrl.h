#ifndef ABSDARTSCTRL_H
#define ABSDARTSCTRL_H
#include "DartControllerContext/SLAs/absgamectrl.h"
#include "DartsController/DCInputSLAs/dcinput.h"
#include "ctrlslas.h"
#include "DartsModelsContext/SLAs/absdartsctx.h"
class AbsDartsCtx;
class AbsDartsCtrl : public AbsGameCtrl, public CtrlSLAs
{
    Q_OBJECT
public:
    AbsDartsCtrl *setModelsContext(AbsDartsCtx *context)
    {
        _modelsContext = context;
        return this;
    }
    AbsDartsCtx *mdsCtx()
    {
        if(_modelsContext != nullptr)
            return _modelsContext;
        throw "Modelscontext not set!";
    }
    Q_INVOKABLE virtual int initialize(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual QByteArray getPlayerScores() const = 0;
    Q_INVOKABLE virtual QByteArray getTurnValues() const = 0;
signals:
    void initialized();
    void controllerAwaitsInput();
    void updateTournamentIndex(const QByteArray &json);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void updatePlayerScore(const QByteArray& json);
    void sendDartsScores(const QByteArray& json);
    void sendOrderedInputs(const QByteArray &json);
private:
    AbsDartsCtx *_modelsContext = nullptr;
};
#endif
