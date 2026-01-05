#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include <QString>
#include "src/input/inputCandidate.h"

class IClosureFilter {
public:
  virtual void init(bool enabled, const QString &mod = "D") = 0;
  virtual void initFromFile() = 0;
  virtual void saveState() = 0;
  virtual const QList<InputCandidate> filter(const QList<InputCandidate> &candidates) = 0;
};

#endif // IDARTINPUTEVALUTOR_H
