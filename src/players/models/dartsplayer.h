#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include <QJsonObject>
#include <QString>

class DartsPlayer {
public:
  DartsPlayer();

  DartsPlayer(const QString& name);

  DartsPlayer(const QJsonObject& jsonObj);
  QJsonObject jsonObject() const;
  QString name() const;
  bool winner() const;
  void setWinner(bool status);

private:
  QString _name = "";
  bool _winner = false;
};

#endif // DARTSPLAYER_H
