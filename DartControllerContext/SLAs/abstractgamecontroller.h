#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H
#include <QObject>
#include <quuid.h>
#include "DartsModelsContext/SLAs/abstractdartscontext.h"
class AbstractGameController : public QObject
{
    Q_OBJECT
public:
    void setModelsContext(AbstractDartsContext *context)
    {
        _modelsContext = context;
    }
    AbstractDartsContext *modelsContext()
    {
        if(_modelsContext != nullptr)
            return _modelsContext;
        throw "Modelscontext not set!";
    }
    Q_INVOKABLE virtual QString tournamentId() const = 0;
public slots:
    virtual void handleUserInput(const QByteArray& json) = 0;
    virtual void createJsonResponse() = 0;
    virtual void undoTurn() = 0;
    virtual void redoTurn() = 0;
    virtual void createIndexJson() = 0;
    virtual void sendTournamentId() = 0;
    virtual void reset() = 0;
    virtual void requestStatus() = 0;
signals:
    void ready();
    void resetSucces();
    void sendCurrentTournamentId(const QUuid &tournament);
    void winnerDetermined(const QByteArray& json);
    void controllerIsNotInitialized();
    void winnerDeclared(const QByteArray& json);
    void controllerIsStopped();
private:
    AbstractDartsContext *_modelsContext = nullptr;
};

#endif // ABSTRACTGAMECONTROLLER_H
