#include "dartscontext.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "DbSLAs/iplayer.h"
#include "ByteArrayServices/converttobytearray.h"
bool DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    auto tournament = tournamentBuilder()->createModel(json);
    auto players = playersContext()->players(playerIndexes);
    setTournamentPlayerDetails()->setDetails(tournament,players);
    dartsDbCtx()->add(tournament);
    return saveToStorage()->save(dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice());
}
bool DartsContext::isConsistent(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,dartsDbCtx()->models());
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb()->models());
    return verifyConsistency()->verify(tournament,inputs,playersContext());
}
bool DartsContext::tryRepair(const QUuid &tournamentId)
{
    auto tournament = getTournament()->get(tournamentId,dartsDbCtx()->models());
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb()->models());
    tournamentRepair()->repair(tournament,inputs,playersContext());
    return saveToStorage()->save({{dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice()},{inputsDb()->models(),inputModelsToJson(),inputConverter(),ioDevice()}});
}
bool DartsContext::setTournamentWinner(const QUuid &tournamentId, const QString &name)
{
    auto player = playersContext()->player(name);
    setTnmWinner()->setWinner(tournamentId,dartsDbCtx()->models(),player->name(),player->id());
    return saveToStorage()->save(dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice());
}
QByteArray DartsContext::inputs(const QUuid &tournamentId) const
{
    auto inputs = getInputsFromDb()->getDisplayed(tournamentId,inputsDb()->models());
    return createJsonFromInputs()->toJson(inputs,inputConverter());
}
bool DartsContext::deleteTournaments(const QVector<int> &indexes)
{
    auto tournamentIds = getTournamentIds()->get(indexes,dartsDbCtx());
    removeInputs()->removeByTournamentIds(tournamentIds,inputsDb());
    dartsDbCtx()->remove(indexes);
    return saveToStorage()->save({{dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice()}, {inputsDb()->models(),inputModelsToJson(),inputConverter(),ioDevice()}});
}
QByteArray DartsContext::tournaments()
{
    return dartsJsonBuilder()->create(dartsDbCtx()->models(),dartsConverter());
}
QByteArray DartsContext::tournament(const int &idx) const
{
    return dartsJsonBuilder()->create(dartsDbCtx()->model(idx),dartsConverter());
}
QByteArray DartsContext::tournament(const QString &id) const
{
    return dartsJsonBuilder()->create(getTournament()->get(QUuid::fromString(id),dartsDbCtx()->models()),dartsConverter());
}
QByteArray DartsContext::tournament(const QUuid &id) const
{
    auto json = dartsConverter()->create(getTournament()->get(id,dartsDbCtx()->models()));
    return ConvertToByteArray::toByteArray(json);
}
bool DartsContext::addInput(const QUuid &tournamentId, const QByteArray &byteArray)
{
    auto input = inputConverter()->create(byteArray);
    setInputHint()->setVisible(input);
    inputsDb()->add(input);
    removeInputs()->removeHidden(tournamentId,inputsDb());
    return saveToStorage()->save(inputsDb()->models(),inputModelsToJson(),inputConverter(),ioDevice());
}
bool DartsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb());
    resetDarts()->reset(tournamentId,dartsDbCtx());
    return saveToStorage()->save({{dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice()}, {inputsDb()->models(),inputModelsToJson(),inputConverter(),ioDevice()}});
}

QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentId)
{
    return dartsJsonBuilder()->create(getTournament()->get(tournamentId,dartsDbCtx()->models()),dartsConverter());
}
bool DartsContext::updateTournamentIndex(QUuid tournament, const QByteArray &indexByteArray)
{
    auto index = indexBuilder()->create(indexByteArray);
    updateIndex()->update(index,tournament,dartsDbCtx());
    return saveToStorage()->save(dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice());
}
QByteArray DartsContext::input(const QUuid &tournament, const QString &name,  const QByteArray &indexByteArray) const
{
    auto index = indexBuilder()->create(indexByteArray);
    auto playerId = playersContext()->player(name)->id();
    auto meta = createMeta()->create(tournament,playerId);
    auto input = getInputsFromDb()->get(meta,index,inputsDb()->models());
    return ConvertToByteArray::toByteArray(inputConverter()->create(input));
}
bool DartsContext::hideInput(QUuid tournament, QString name, const QByteArray &indexByteArray)
{
    auto idx = indexBuilder()->create(indexByteArray);
    auto playerId = playersContext()->player(name)->id();
    auto meta = createMeta()->create(tournament,playerId);
    setInputHint()->setHidden(idx,meta,inputsDb()->models(),getInputsFromDb());
    updateIndex()->update(idx,tournament,dartsDbCtx());
    return saveToStorage()->save({{dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice()}, {inputsDb()->models(),inputModelsToJson(),inputConverter(),ioDevice()}});
}
bool DartsContext::revealInput(QUuid tournament, QString name, const QByteArray &indexByteArray)
{
    auto idx = indexBuilder()->create(indexByteArray);
    auto playerId = playersContext()->player(name)->id();
    auto meta = createMeta()->create(tournament,playerId);
    updateIndex()->update(idx,tournament,dartsDbCtx());
    setInputHint()->setVisible(idx,meta,inputsDb()->models(),getInputsFromDb());
    return saveToStorage()->save({{dartsDbCtx()->models(),tournamentsToJson(),dartsConverter(),ioDevice()}, {inputsDb()->models(),inputModelsToJson(),inputConverter(),ioDevice()}});
}
