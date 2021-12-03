#include "dartscontroller.h"
int DartsController::handleInput(const QByteArray& json)
{
    if(metaContext()->get().status == statusCodes()->winnerFound()) return -1;
    auto input = createInput()->create(json);
    auto scoreCand = scoreCalc()->calc(idxCtrl()->index(),input.score,scoresContext());
    inputEval()->evaluate(input,scoreCand,metaContext(),this,statusCodes(),playersContext());
    return 0;
}
void DartsController::addInputToModelsContext(DCIptVals &input)
{
    setInputStats()->set(input);
    mdsCtx()->addInput(metaContext()->get().tournamentId,iptConverter()->convert(input),[=]{
        auto index = idxCtrl()->next();
        mdsCtx()->updateTournamentIndex(metaContext()->get().tournamentId,idxConverter()->convert(index),[=]{
            updateScoreDetails(input);
            emit updatePlayerScore(createJson()->create(input));
        });
    });
}
void DartsController::updateScoreDetails(const DCIptVals &input)
{
    updatePlayerStats()->update(input,statsContext());
    playersContext()->updateStatus(input.playerName,input.inGame);
    scoresContext()->score(input.playerName).remainingScore = input.remainingScore;
}
QByteArray DartsController::getPlayerScores() const
{
    return createJson()->create(scoresContext()->scores(),statsContext()->stats());
}
void DartsController::reset()
{
    DCResetContexts::reset(idxCtrl(),scoresContext(),statsContext(),metaContext(),playersContext(),statusCodes());
    mdsCtx()->resetTournament(metaContext()->get().tournamentId,[=]{emit resetSucces();});
}
int DartsController::status() const
{
    return metaContext()->get().status;
}
void DartsController::undoTurn()
{
    auto inputIdx = idxCtrl()->undo();
    auto meta = createMeta()->create();
    mdsCtx()->hideInput(meta.tournamentId,meta.playerName,idxConverter()->convert(inputIdx),[=]{
        auto reqIndex = reqIndexBuilder()->prevIdx();
        auto cvtIdx = idxConverter()->convert(reqIndex);
        auto mdIpt = mdsCtx()->input(meta.tournamentId,meta.playerName,cvtIdx);
        auto ipt = iptConverter()->convert(mdIpt);
        updateScoreDetails(ipt);
        emit updatePlayerScore(createJson()->create(ipt));
    });
}
void DartsController::redoTurn()
{
    auto meta = createMeta()->create();
    auto idx = idxConverter()->convert(idxCtrl()->index());
    idxCtrl()->redo();
    mdsCtx()->revealInput(meta.tournamentId,meta.playerName,idx,[=]{
        auto mdlInput = mdsCtx()->input(meta.tournamentId,meta.playerName,idx);
        auto ipt = iptConverter()->convert(mdlInput);
        updateScoreDetails(ipt);
        emit updatePlayerScore(createJson()->create(ipt));
    });
}
int DartsController::initialize(const QUuid &tId)
{
    DCInit::initTournamentMeta(mdsCtx()->tournament(tId),metaContext(),idxCtrl(),idxConverter());
    DCInit::initPlayerDetails(mdsCtx()->players(tId),metaContext()->get(),scoresContext(),scoresBuilder(),statsContext(),playersContext());
    DCInit::initScores(iptConverter()->convert(mdsCtx()->inputs(tId)),updatePlayerScores(),updatePlayerStats(),scoresContext(),statsContext());
    return statusCodes()->initialized();
}
QString DartsController::tournamentId() const
{
    return metaContext()->get().tournamentId.toString(QUuid::WithBraces);
}
QByteArray DartsController::getTurnValues() const
{
    return createJson()->create(turnValuesBuilder()->turnValues());
}
QByteArray DartsController::getWinnerJson() const
{
    return createJson()->create(createMeta()->winnerMeta());
}
