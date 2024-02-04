#ifndef IDARTPLAYERS_H
#define IDARTPLAYERS_H

#include <QStringList>

class DartsPlayer;
class QByteArray;

class IDartsPlayers {
public:
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual void reset() = 0;
        virtual int playersCount() const = 0;
        virtual bool saveState() = 0;
        virtual QByteArray allAsJson() const = 0;
        virtual DartsPlayer& one(const int& index) = 0;
        virtual DartsPlayer& one() = 0;
        virtual DartsPlayer& one(const QString& name) = 0;
        virtual DartsPlayer winner() const = 0;
        virtual const QStringList names() const = 0;
};

#endif // IDARTPLAYERS_H
