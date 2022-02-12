#ifndef IDCINPUTEVALUATOR_H
#define IDCINPUTEVALUATOR_H
#include <qobject.h>
struct DCPlayer;
struct DCMeta;
struct DCInput;
class IDCInputEvaluator : public QObject
{
    Q_OBJECT
public:
    virtual void evaluate(DCInput &input) = 0;
};
#endif // IPOINTVALIDATOR_H
