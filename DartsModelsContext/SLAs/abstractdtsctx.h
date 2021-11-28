#ifndef ABSTRACTDTSCTX_H
#define ABSTRACTDTSCTX_H
#include "ModelsContext/ModelsContextSLAs/abstractmdsctx.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/InputModels/diptvals.h"
class AbstractDtsCtx : public AbstractMdsCtx
{
    Q_OBJECT
public:
    AbstractPlayersContext *playersContext() const
    {
        return _playersContext;
    }
    AbstractDtsCtx *setPlayersContext(AbstractPlayersContext *newPlayersContext)
    {
        _playersContext = newPlayersContext;
        return this;
    }
    Q_INVOKABLE virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    virtual AbstractDartsInput *input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const = 0;
    virtual void addInput(const QUuid &tournamentId, DIptVals input, std::function<void()> func) = 0;
    virtual void hideInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func) = 0;
    virtual void revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func) = 0;
    virtual QVector<AbstractDartsInput*> inputs(const QUuid &tournamentId) const = 0;
    virtual void updateTournamentIndex(const QUuid &tournament, IDartsIndex *index, std::function<void()> func) = 0;
    virtual AbstractDartsTournament *tournament(const QUuid &id) const override= 0;
signals:
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json);
    void tournamentModelsStatePersisted();
    void tournamentCreatedOk();
    void tournamentCreatedFail();
    void sendOrderedInputs(const QByteArray& scores);
private:
    AbstractPlayersContext *_playersContext;
};




#endif // ABSTRACTDARTSCONTEXT_H
