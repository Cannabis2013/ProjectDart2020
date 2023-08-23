#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <DartsController/Contracts/Controller/idartsctrl.h>
#include <DartsController/Contracts/Routines/dartscontrollerroutines.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>

class DartsController : public IDartsCtrl,
                        public DartsControllerRoutines,
                        public DCServices {
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
        IDCAddInput *_addToModelsCtx;
        IDCResetServices *_resetServices;
        IDCUndoTurn *_undoTurn;
        IDCRedoTurn *_redoTurn;
        IDCCreateWinnerJson *_createWinnerReport;
        IDCGetTurnValuesAsJson *_getTurnValuesAsJson;
        IDCGetScoresAsJson *_getPlayersAsJson;
};
#endif // FIVEHUNDREDANDONEGAME_H
