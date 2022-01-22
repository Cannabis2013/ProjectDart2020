#ifndef ABSDARTSCTRL_H
#define ABSDARTSCTRL_H
#include <qobject.h>
#include "DCTurnValuesSLAs/dcturnvaluesslas.h"
#include "DCIndexSLAs/dcindexslas.h"
#include "DCScoresSLAs/dcplayersslas.h"
#include "DCJsonSLAs/dcjsonslas.h"
#include "DCMetaSLAs/dcmetaslas.h"
#include "DCInputSLAs/dcinputsslas.h"
#include "PlayerStatsSLAs/dcinputstatsslas.h"
#include "DCFinishesSLAs/dcfinishesservices.h"
class AbsDartsCtx;
class AbsDartsCtrl : public QObject,
                     public DCMetaSLAs,
                     public DCFinishesSLAs,
                     public DCTurnvaluesSLAs,
                     public DCJsonSLAs,
                     public DCPlayersSLAs,
                     public DCInputsSLAs,
                     public DCIndexSLAs,
                     public PlayerStatsSLAs
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual QString tournamentId() const = 0;
    Q_INVOKABLE virtual QByteArray undoTurn() = 0;
    Q_INVOKABLE virtual QByteArray redoTurn() = 0;
    Q_INVOKABLE virtual QByteArray addInput(const QByteArray& json) = 0;
    Q_INVOKABLE virtual bool reset() = 0;
    Q_INVOKABLE virtual int status() const = 0;
    Q_INVOKABLE virtual QByteArray getWinnerJson() const = 0;
    Q_INVOKABLE virtual int initialize(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual QByteArray getPlayerScores() const = 0;
    Q_INVOKABLE virtual QByteArray getTurnValues() const = 0;
    void setModelsContext(AbsDartsCtx *context) {_modelsContext = context;}
    AbsDartsCtx *mdsCtx() {return _modelsContext;}
signals:
    void inputPersistedOk();
private:
    AbsDartsCtx *_modelsContext = nullptr;
};
#endif
