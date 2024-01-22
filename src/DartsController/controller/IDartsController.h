#ifndef IDARTSCONTROLLER_H
#define IDARTSCONTROLLER_H

#include <QByteArray>
#include <QStringList>

class IDartsController {
public:
        virtual void init(const QByteArray& json) = 0;
        virtual void initFromSaved() = 0;
        virtual void reset() = 0;
        virtual void saveState() = 0;
        virtual QByteArray playerScores() const = 0;
        virtual QByteArray allPlayers() const = 0;
        virtual QByteArray turnReport() const = 0;
        virtual QByteArray statisticReport() const = 0;
        virtual void addInput(const QString& mod, const int& point) = 0;
        virtual void undoTurn() = 0;
        virtual void redoTurn() = 0;
        virtual void skipTurn() = 0;
};

#endif // IDARTSCONTROLLER_H
