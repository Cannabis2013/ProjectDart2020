#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "idartsplayers.h"
#include "src/players/models/dartsplayer.h"
#include <qstringlist.h>

class DartsPlayers : public IDartsPlayers
{
public:
  DartsPlayers(const QString& filepath);
  void init(const QStringList& names) override;
  void initFromFile() override;
  QList<DartsPlayer>& all() override;
  QList<DartsPlayer>& available() override;
  int count() override;
  bool saveState() override;

private:
  QList<DartsPlayer> _players;
  const QString _storagePath;
  QList<DartsPlayer> _available;
  int _count = -1;
};

#endif // DARTPLAYERS_H
