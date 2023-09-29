#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <DartsController/Contracts/Controller/idartscontroller.h>
#include <DartsController/Contracts/Routines/dartscontrollerroutines.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>

class DartsController : public IDartsController
{
    Q_OBJECT
public:
    int initialize(const QUuid &tournamentId) override;
    QString tournamentId() const override;
    QByteArray getPlayerScores() const override;
    QByteArray addInput(const QByteArray &json) override;
    QByteArray undoTurn() override;
    QByteArray redoTurn() override;
    QByteArray getTurnValues() const override;
    QByteArray getWinnerJson() const override;
    bool reset() override;
    int status() const override;

private:
    AbstractDartsContext *_modelsContext = nullptr;
    DCMetaServices *_metaServices;
    DCFinishServices *_finServices;
    DCPlayersServices *_playerServices;
    DCInputsServices *_inputServices;
    DCIndexServices *_indexServices;
    IDCInitialize *_initialize;
    IDCAddInput *_inputPersist;
    IDCResetServices *_resetServices;
    IDCUndoTurn *_undoTurn;
    IDCRedoTurn *_redoTurn;
    IDCCreateWinnerJson *_createWinnerReport;
    IDCGetTurnValuesAsJson *_getTurnValuesAsJson;
    IDCGetScoresAsJson *_playerScores;
};
#endif // FIVEHUNDREDANDONEGAME_H
