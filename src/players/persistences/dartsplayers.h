#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "idartsplayers.h"
#include <qstringlist.h>

class DartsPlayers : public IDartsPlayers
{
public:
  DartsPlayers(const QString& filepath);
  void init(const QStringList& playerNames) override;
  void initFromFile() override;
  void reset() override;
  QStringList& all() override;
  bool saveState() override;

private:
  QStringList _playerNames;
  const QString _storagePath;
};

#endif // DARTPLAYERS_H
