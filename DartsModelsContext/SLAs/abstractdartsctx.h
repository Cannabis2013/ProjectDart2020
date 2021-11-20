#ifndef ABSTRACTDARTSCTX_H
#define ABSTRACTDARTSCTX_H
#include "ModelsContext/ModelsContextSLAs/abstractmdsctx.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
class AbstractDartsCtx : public AbstractMdsCtx
{
    Q_OBJECT
public:
    AbstractPlaCtx *playersContext() const
    {
        return _playersContext;
    }
    AbstractDartsCtx *setPlayersContext(AbstractPlaCtx *newPlayersContext)
    {
        _playersContext = newPlayersContext;
        return this;
    }
    Q_INVOKABLE virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    virtual AbstractDartsInput *input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const = 0;
    virtual void addInput(const QUuid &tournamentId, AbstractDartsInput *input, std::function<void()> func) = 0;
    virtual void hideInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func) = 0;
    virtual void revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func) = 0;
    virtual QVector<IModel<QUuid>*> tournamentInputs(const QUuid &tournamentId) const = 0;
    virtual QFuture<bool> updateTournamentIndex(const QUuid &tournament, IDartsIndex *index) = 0;
    virtual AbstractDartsTournament *tournament(const QUuid &id) const override= 0;
signals:
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json);
    void tournamentModelsStatePersisted();
    void tournamentCreatedOk();
    void tournamentCreatedFail();
    void sendOrderedInputs(const QByteArray& scores);
private:
    AbstractPlaCtx *_playersContext;
};




#endif // ABSTRACTDARTSCONTEXT_H
