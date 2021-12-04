#ifndef ABSTRACTDARTSCONTEXT_H
#define ABSTRACTDARTSCONTEXT_H
#include "ModelsContext/ModelsContextSLAs/abstractmodelscontext.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/InputModels/diptvals.h"
class AbstractDartsContext : public AbstractModelsContext
{
    Q_OBJECT
public:
    AbstractPlayersContext *playersContext() const
    {
        return _playersContext;
    }
    void setPlayersContext(AbstractPlayersContext *newPlayersContext) {_playersContext = newPlayersContext;}
    Q_INVOKABLE virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    virtual AbstractDartsInput *input(const QUuid &tournament, const QString &name, IDartsIndex *index) const = 0;
    virtual bool addInput(QUuid tournamentId, DIptVals input) = 0;
    virtual bool hideInput(QUuid tournament, QString name, IDartsIndex *index) = 0;
    virtual bool revealInput(QUuid tournament, QString name, IDartsIndex *index) = 0;
    virtual QVector<AbstractDartsInput*> inputs(const QUuid &tournamentId) const = 0;
    virtual bool updateTournamentIndex(QUuid tournament, IDartsIndex *index) = 0;
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
