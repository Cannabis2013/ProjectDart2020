#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <icontroller.h>
#include <quuid.h>
#include "iresponseinterface.h"
#include <QVariantList>

typedef IController<QUuid,QString> DefaultControllerInterface;

class AbstractGameController : public QObject,
        public DefaultControllerInterface,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:
    /*
     * Public types
     */

public slots:
    virtual void handleAndProcessUserInput(const int &point, const int &modifierKeyCode) = 0;
    virtual void start() = 0;
    virtual void stop() = 0 ;
    /*
     * Set current tournament
     *  - Request basic tournament data from datacontext
     *  - Request index values from datacontext
     */
    virtual void setCurrentTournament(const int &index) = 0;

    /*
     * Handle request and response from different contexts
     */

    virtual void handleRequestFromContext(const int &request, const QVariantList &args) override = 0;
    virtual void handleResponseFromContext(const int &response, const QVariantList &args) override = 0;
    /*
     * Handle requests from datacontext
     */
    virtual void handleControllerStateRequest() = 0;
    /*
     * Undo/redo turn
     */
    virtual QUuid undoTurn() = 0;
    virtual QUuid redoTurn() = 0;

    virtual void resetGame() = 0;

signals:
    void transmitResponse(const int &status, const QVariantList &args);
    void sendRequestToContext(const int &request, const QVariantList &args);
    void sendResponseToContext(const int &response, const QVariantList &args);
};

#endif // ABSTRACTGAMECONTROLLER_H
