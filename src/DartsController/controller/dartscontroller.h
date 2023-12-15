#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include "src/DartsController/controller/IDartsController.h"
#include "src/DartsController/controller/controllerservices.h"
#include <QObject>

class DartsController : public QObject, public ControllerServices, public IDartsController {
        Q_OBJECT
public:
        Q_INVOKABLE void init(const QByteArray& json) override;
        Q_INVOKABLE void initFromSaved() override;
        Q_INVOKABLE void reset() override;
        Q_INVOKABLE void saveState() override;
        Q_INVOKABLE QByteArray playerScores() const override;
        Q_INVOKABLE QStringList playerNames() const override;
        QString winnerImage() const override;
        Q_INVOKABLE QByteArray turnInfo() const override;
        Q_INVOKABLE void addInput(const QString& mod, const int& point) override;
        Q_INVOKABLE void undoTurn() override;
        Q_INVOKABLE void redoTurn() override;
        Q_INVOKABLE void skipTurn() override;
};
#endif // FIVEHUNDREDANDONEGAME_H
