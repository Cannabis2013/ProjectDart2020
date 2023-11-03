#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include "src/DartsController/controller/abstractdartscontroller.h"
#include <QObject>

class DartsController : public QObject, public AbstractDartsController {
        Q_OBJECT
public:
        Q_INVOKABLE void init(const QStringList& playerNames, const int& mode, const int& initialScore);
        Q_INVOKABLE void initFromSaved();
        Q_INVOKABLE void reset();
        Q_INVOKABLE void saveState();
        Q_INVOKABLE QByteArray playerScores() const;
        Q_INVOKABLE QStringList playerNames() const;
        Q_INVOKABLE QByteArray turnInfo() const;
        Q_INVOKABLE void addInput(const QString& mod, const int& point);
        Q_INVOKABLE void undoTurn();
        Q_INVOKABLE void redoTurn();
        Q_INVOKABLE void skipTurn();
};
#endif // FIVEHUNDREDANDONEGAME_H
