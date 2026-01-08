#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include <QObject>
#include "idartsplayers.h"
#include <qstringlist.h>

class DartsPlayers : public IDartsPlayers
{
  public:
    virtual QStringList& all() override;
    void init(const QStringList& playerNames) override;
    void initFromFile() override;
    bool saveState() override;

  private:
    QStringList _playerNames;
    const QString _storagePath = "players.dat";
};

#endif // DARTPLAYERS_H
