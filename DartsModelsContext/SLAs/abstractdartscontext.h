#ifndef ABSTRACTDARTSCONTEXT_H
#define ABSTRACTDARTSCONTEXT_H
#include "ModelsContext/ModelsContextSLAs/abstractmodelscontext.h"
class AbstractDartsContext : public AbstractModelsContext
{
    Q_OBJECT
public slots:
    virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    virtual QByteArray createDartsKeyValues(const QUuid& tournament) = 0;
    virtual QFuture<bool> updateTournamentIndex(const QByteArray &json) = 0;
    virtual QFuture<QByteArray> addInput(const QByteArray& json) = 0;
    virtual QFuture<QByteArray> hideInput(const QByteArray &json) = 0;
    virtual QFuture<QByteArray> revealInput(const QByteArray &json) = 0;
    virtual QByteArray createDartsValuesJson(const QUuid& tournament) = 0;
signals:
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json);
    void tournamentModelsStatePersisted();
    void tournamentCreatedAndPersisted();
    void sendOrderedInputs(const QByteArray& scores);
};
#endif // ABSTRACTDARTSCONTEXT_H
