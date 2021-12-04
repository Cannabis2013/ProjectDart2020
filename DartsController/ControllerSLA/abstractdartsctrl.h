#ifndef ABSTRACTDARTSCTRL_H
#define ABSTRACTDARTSCTRL_H
#include "DartControllerContext/SLAs/abstractgamecontroller.h"
#include "DartsController/DCInputSLAs/dcinput.h"
class AbstractDartsCtrl : public AbstractGameController
{
    Q_OBJECT
public:
    AbstractDartsCtrl *setModelsContext(AbstractDartsContext *context)
    {
        _modelsContext = context;
        return this;
    }
    AbstractDartsContext *mdsCtx()
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
    AbstractDartsContext *_modelsContext = nullptr;
};
#endif
