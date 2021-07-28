#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <AbstractApplicationInterface.h>
#include <dartapplicationservices.h>
#include <QFuture>
#include <qfuturewatcher.h>
#include <functional>

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication :
        public AbstractApplicationInterface,
        public DartApplicationServices
{
    Q_OBJECT
public:
    // Public types
    typedef QVector<const IModel<QUuid>*> Models;
    // Public interface
    void createDartsTournamentFromJson(const QByteArray &json) override;
public slots:
    void handleSendGameModesRequest() const override;
    //Set game controller methods
    void setDartsPointController(AbstractDartsController *controller) override;
    void setDartsScoreController(AbstractDartsController *controller) override;
private:
    // Run asynchronously tasks
    using Func = std::function<void()>;
    template<typename T>
    void runAsync(Func funct, const QFuture<T> &future);
    // Clear controller..
    void clearGameController();
};
#endif // PROJECTDARTINTERFACE_H
