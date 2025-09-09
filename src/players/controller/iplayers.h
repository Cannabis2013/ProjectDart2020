#ifndef IPLAYERS_H
#define IPLAYERS_H

class QString;
class QByteArray;

class IPlayers {
public:
  virtual QByteArray all() const = 0;
  virtual QByteArray available() const = 0;
  virtual QString current() const = 0;
  virtual bool isWinnerFound() const = 0;
  virtual QByteArray winnerInfo() const = 0;
  virtual int playerIndex(const QString& name) const = 0;
  virtual QByteArray report() const = 0;
};

#endif // IPLAYERS_H
