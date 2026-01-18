#ifndef DCFINISHBUILDER_H
#define DCFINISHBUILDER_H

#include "finishconstructor.h"

#include <QObject>

class DartsFinishes : public QObject
{
    Q_OBJECT
  public:
    DartsFinishes();
    Q_INVOKABLE QString finish(const int& remainingScore, const int& turnIndex) const;

  private:
    QString getTargetRow(const int& turnIndex, const int& remainingScore) const;

    FinishConstructor::Finishes* _finishes;

    FinishConstructor* _finishConstructor = new FinishConstructor();
};
#endif // SCORECONTROLLER_H

