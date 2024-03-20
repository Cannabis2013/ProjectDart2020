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
        virtual bool saveState() = 0;
        virtual QList<DartsPlayer>& all() = 0;
};

#endif // IDARTPLAYERS_H
