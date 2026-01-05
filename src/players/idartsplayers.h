#ifndef IDARTPLAYERS_H
#define IDARTPLAYERS_H

#include <QStringList>
#include <qstringlist.h>

class DartsPlayer;
class QByteArray;

class IDartsPlayers {
public:
  virtual QStringList& all() = 0;
  virtual void init(const QStringList& names) = 0;
  virtual void initFromFile() = 0;
  virtual void reset() = 0;
  virtual bool saveState() = 0;
};

#endif // IDARTPLAYERS_H
