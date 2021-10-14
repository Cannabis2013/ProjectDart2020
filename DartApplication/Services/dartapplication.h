#ifndef DARTAPPLICATION_H
#define DARTAPPLICATION_H

#include "DartApplication/SLAs/dartapplicationslas.h"
#include <QFuture>
#include <qfuturewatcher.h>
#include <functional>

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication : public DartApplicationSLAs
{
    Q_OBJECT
public:
    // Public types
    typedef QVector<IModel<QUuid>*> Models;
    // Public interface
    void addDartsTournaments(const QByteArray &json) override;
public slots:
    void handleSendGameModesRequest() override;
    //Set game controller methods
    void setDartsController(AbstractDartsController *controller) override;
private:
    // Run asynchronously tasks
    template<typename T>
    void runAsync(std::function<void()> funct, const QFuture<T> &future);
    // Clear controller..
    void clearGameController();
};
#endif // DARTAPPLICATION_H
