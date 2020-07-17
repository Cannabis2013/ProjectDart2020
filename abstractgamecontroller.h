#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <icontroller.h>

#include "defaultdatacontextinterface.h"

typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;
typedef IController<QUuid,QString,DefaultDataInterface> DefaultControllerInterface;

class AbstractGameController : public QObject, public DefaultControllerInterface
{
    Q_OBJECT
public:
    /*
     * Public types
     */
    enum GameStatus {GameControllerIdle = 0x9,
                     GamecontrollerBusy = 0xa, // Game is idle but in progress
                     GameControllerStopped = 0xb, // Game is stopped and no longer accepts input
                     GameControllerAwaitsInput = 0xc, // This should indicate that the gamecontroller is in a state where it awaits new player input
                     GameControllerRunning = 0xd,
                     GameControllerWinnerDeclared = 0xe,
                     GameControllerNotInitialized = 0xf};
    void setDataContext(DefaultDataInterface *context)
    {
        _dataContext = context;
    }
    DefaultDataInterface *dataContext(){
        return _dataContext;
    }

public slots:
    virtual int start() = 0;
    virtual int stop() = 0 ;

signals:
    void sendStatus(const int &status);
    void stateChanged();

private:
    DefaultDataInterface *_dataContext;

};

#endif // ABSTRACTGAMECONTROLLER_H
