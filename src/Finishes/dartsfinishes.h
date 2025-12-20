#ifndef DCFINISHBUILDER_H
#define DCFINISHBUILDER_H

#include "dartscreatefinishes.h"

#include <QObject>

class DartsFinishes : public QObject
{
    Q_OBJECT
  public:
    DartsFinishes();
    Q_INVOKABLE QString finish(const int& remainingScore, const int& turnIndex) const;

  private:
    QString getTargetRow(const int& turnIndex, const int& remainingScore) const;

    FinishesTypes::TargetRows* _finishes;

    DartsCreateFinishes* _constructRow = new DartsCreateFinishes();
};
#endif // SCORECONTROLLER_H

