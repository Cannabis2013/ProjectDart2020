#ifndef IDARTPLAYERS_H
#define IDARTPLAYERS_H

#include <qstring.h>

class IDartsPlayers
{
public:
        virtual void initPlayers(const QStringList &names) = 0;
        virtual void initPlayers() = 0;
        virtual int playersCount() const = 0;
        virtual bool saveState() = 0;
        virtual int indexOf(const QString& name) const = 0;
        virtual QString name(int index) const = 0;
        virtual QString name() const = 0;
        virtual QString winnerName() const = 0;
        virtual void declareAsWinner(const QString& name) = 0;
        virtual const QStringList names() const = 0;
};

#endif // IDARTPLAYERS_H
