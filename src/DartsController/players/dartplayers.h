#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "IDartPlayers.h"

#include <qstringlist.h>

class DartPlayers : public IDartPlayers
{
public:
        DartPlayers();

        virtual void initPlayers(const QStringList& names) override;
        virtual void initPlayers() override;
        virtual QString name(int index) const override;
        virtual int playersCount() override;
        virtual QStringList  names() const override;
private:
        void initFromFile();
        void saveToFile();

        QStringList _playerNames;
};

#endif // DARTPLAYERS_H
