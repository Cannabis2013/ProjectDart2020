#include "dartscontroller.h"
QByteArray DartsController::addInput(const QByteArray& json)
{
    if(metaContext()->get().status == statusCodes()->winnerFound()) return QByteArray();
    auto input = createInput()->create(json);
    auto scoreCand = scoreCalc()->calc(idxCtrl()->index(),input.score,scoresContext());
    return inputEval()->evaluate(input,scoreCand,metaContext(),this,statusCodes(),playersContext());
}
QByteArray DartsController::addInputToModelsContext(DCIptVals &input)
{
    setInputStats()->set(input);
    auto index = idxCtrl()->next();
    mdsCtx()->addInput(metaContext()->get().tournamentId,iptConverter()->convert(input));
    mdsCtx()->updateTournamentIndex(metaContext()->get().tournamentId,idxConverter()->convert(index));
    updateScoreDetails(input);
    return createJson()->create(input);
}
void DartsController::updateScoreDetails(const DCIptVals &input)
{
    updatePlayerStats()->update(input,statsContext());
    playersContext()->updateStatus(input.playerName,input.inGame);
    scoresContext()->score(input.playerName).remScore = input.remainingScore;
}
QByteArray DartsController::getPlayerScores() const
{
    return createJson()->create(scoresContext()->scores(),statsContext()->stats());
}
bool DartsController::reset()
{
    DCResetContexts::reset(idxCtrl(),scoresContext(),statsContext(),metaContext(),playersContext(),statusCodes());
    return mdsCtx()->resetTournament(metaContext()->get().tournamentId);
}
int DartsController::status() const
{
    return metaContext()->get().status;
}
QByteArray DartsController::undoTurn()
{
    auto inputIdx = idxCtrl()->undo();
    auto meta = createMeta()->create();
    mdsCtx()->hideInput(meta.tournamentId,meta.playerName,idxConverter()->convert(inputIdx));
    auto reqIndex = reqIndexBuilder()->prevIdx();
    auto cvtIdx = idxConverter()->convert(reqIndex);
    auto mdIpt = mdsCtx()->input(meta.tournamentId,meta.playerName,cvtIdx);
    auto ipt = iptConverter()->convert(mdIpt,createInput());
    updateScoreDetails(ipt);
    return createJson()->create(ipt);
}
QByteArray DartsController::redoTurn()
{
    auto meta = createMeta()->create();
    auto idx = idxConverter()->convert(idxCtrl()->index());
    idxCtrl()->redo();
    mdsCtx()->revealInput(meta.tournamentId,meta.playerName,idx);
    auto mdlInput = mdsCtx()->input(meta.tournamentId,meta.playerName,idx);
    auto ipt = iptConverter()->convert(mdlInput,createInput());
    updateScoreDetails(ipt);
    return createJson()->create(ipt);
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
