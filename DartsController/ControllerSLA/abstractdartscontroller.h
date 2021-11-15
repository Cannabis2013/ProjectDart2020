#ifndef ABSTRACTDARTSCONTROLLER_H
#define ABSTRACTDARTSCONTROLLER_H
#include "DartControllerContext/SLAs/abstractgamecontroller.h"
class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public:
    AbstractDartsController *setModelsContext(AbstractDartsContext *context)
    {
        _modelsContext = context;
        return this;
    }
    AbstractDartsContext *modelsContext()
    {
        if(_modelsContext != nullptr)
            return _modelsContext;
        throw "Modelscontext not set!";
    }
    Q_INVOKABLE virtual int initialize(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual QByteArray getPlayerScores() = 0;
public slots:
    virtual void addInputToModelsContext(AbstractDartsInput *input) = 0;
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
