#include "dartsctrl.h"
int DartsCtrl::handleInput(const QByteArray& json)
{
    if(metaCtx()->get().status == statusCodes()->winnerFound()) return -1;
    auto input = createInput()->create(json);
    auto scoreCand = scoreCalc()->calc(idxCtrl()->index(),input.score,scoresCtx());
    inputEval()->evaluate(input,scoreCand,metaCtx(),this,statusCodes(),playersCtx());
    return 0;
}
void DartsCtrl::addInputToModelsContext(DCIptVals &input)
{
    setInputStats()->set(input);
    mdsCtx()->addInput(metaCtx()->get().tournamentId,iptConverter()->convert(input),[=]{
        mdsCtx()->updateTournamentIndex(metaCtx()->get().tournamentId,idxConverter()->convert(idxCtrl()->next()),[=]{
            updateScoreDetails(input);
        });
    });
}
void DartsCtrl::updateScoreDetails(const DCIptVals &input)
{
    updatePlayerStats()->update(input,statsCtx());
    playersCtx()->updateStatus(input.playerId,input.inGame);
    auto scoreModel = &scoresCtx()->score(input.playerId);
    scoreModel->remainingScore = input.remainingScore;
    emit updatePlayerScore(createJson()->create(input));
}
QByteArray DartsCtrl::getPlayerScores() const
{
    return createJson()->create(scoresCtx()->scores(),statsCtx()->stats());
}
void DartsCtrl::reset()
{
    DCResetContexts::reset(idxCtrl(),scoresCtx(),statsCtx(),metaCtx(),playersCtx(),statusCodes());
    RunLater::run<bool>(mdsCtx()->resetTournament(metaCtx()->get().tournamentId),[=](const bool &result){if(result)emit resetSucces();});
}
int DartsCtrl::status() const
{
    return metaCtx()->get().status;
}
void DartsCtrl::undoTurn()
{
    auto inputIdx = idxCtrl()->undo();
    auto meta = createMeta()->create();
    mdsCtx()->hideInput(meta.tournamentId,meta.currentPlayerId,idxConverter()->convert(inputIdx),[=]{
        auto reqIndex = reqIndexBuilder()->prevIdx();
        auto mdlInput = mdsCtx()->input(meta.tournamentId,meta.currentPlayerId,idxConverter()->convert(reqIndex));
        updateScoreDetails(iptConverter()->convert(mdlInput));
    });
}
void DartsCtrl::redoTurn()
{
    auto meta = createMeta()->create();
    auto idx = idxConverter()->convert(idxCtrl()->index());
    idxCtrl()->redo();
    mdsCtx()->revealInput(meta.tournamentId,meta.currentPlayerId,idx,[=]{
        auto mdlInput = mdsCtx()->input(meta.tournamentId,meta.currentPlayerId,idx);
        updateScoreDetails(iptConverter()->convert(mdlInput));
    });
}
int DartsCtrl::initialize(const QUuid &tId)
{
    DCInit::initTournamentMeta(mdsCtx()->tournament(tId),metaCtx(),idxCtrl(),idxConverter());
    DCInit::initPlayerDetails(mdsCtx()->players(tId),metaCtx()->get(),scoresCtx(),scoresBuilder(),statsCtx(),playersCtx());
    DCInit::initScores(iptConverter()->convert(mdsCtx()->inputs(tId)),updatePlayerScores(),updatePlayerStats(),scoresCtx(),statsCtx());
    return statusCodes()->initialized();
}
QString DartsCtrl::tournamentId() const
{
    return metaCtx()->get().tournamentId.toString(QUuid::WithBraces);
}
QByteArray DartsCtrl::getTurnValues() const
{
    return createJson()->create(turnValuesBuilder()->turnValues());
}
QByteArray DartsCtrl::getWinnerJson() const
{
    return createJson()->create(createMeta()->winnerMeta());
}
