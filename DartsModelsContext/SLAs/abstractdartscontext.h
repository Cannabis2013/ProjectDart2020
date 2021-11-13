#ifndef ABSTRACTDARTSCONTEXT_H
#define ABSTRACTDARTSCONTEXT_H
#include "ModelsContext/ModelsContextSLAs/abstractmodelscontext.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
class AbstractDartsContext : public AbstractModelsContext
{
    Q_OBJECT
public:
    virtual AbstractDartsInput *input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const = 0;
    virtual QFuture<bool> addInput(const QByteArray& json) = 0;
    virtual QFuture<bool> hideInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index) = 0;
    virtual QFuture<bool> revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index) = 0;
    AbstractPlayersContext *playersContext() const
    {
        return _playersContext;
    }
    AbstractDartsContext *setPlayersContext(AbstractPlayersContext *newPlayersContext)
    {
        _playersContext = newPlayersContext;
        return this;
    }
public slots:
    virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    virtual QByteArray createDartsKeyValues(const QUuid& tournament) = 0;
    virtual QFuture<bool> updateTournamentIndex(const QUuid &tournament, IDartsIndex *index) = 0;
    virtual QByteArray createDartsValuesJson(const QUuid& tournament) = 0;
signals:
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json);
    void tournamentModelsStatePersisted();
    void tournamentCreatedAndPersisted();
    void sendOrderedInputs(const QByteArray& scores);
private:
    AbstractPlayersContext *_playersContext;
};




#endif // ABSTRACTDARTSCONTEXT_H
