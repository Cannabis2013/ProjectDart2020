#ifndef IPLAYERS_H
#define IPLAYERS_H

#include <QStringList>

class QString;
class QByteArray;

class IPlayers {
public:
  virtual QStringList all() const = 0;
  virtual QString current() const = 0;
  virtual int playerIndex(const QString& name) const = 0;
};

#endif // IPLAYERS_H
