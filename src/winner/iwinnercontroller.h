#ifndef IWINNERCONTROLLER_H
#define IWINNERCONTROLLER_H

#include <QByteArray>

class IWinnerController
{
  public:
    virtual bool isWinnerFound() const = 0;
    virtual QByteArray info() const = 0;
};

#endif // IWINNERCONTROLLER_H
