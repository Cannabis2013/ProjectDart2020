#ifndef WINNERINFO_H
#define WINNERINFO_H

#include "iwinnercontroller.h"

#include <QObject>

class ServiceCollection;

class WinnerInfo : public QObject, public IWinnerController
{
    Q_OBJECT

  public:
    WinnerInfo(ServiceCollection* services);
    Q_INVOKABLE bool isWinnerFound() const;
    Q_INVOKABLE QByteArray info() const;

  private:
    ServiceCollection* _services;
};

#endif // WINNERINFO_H
