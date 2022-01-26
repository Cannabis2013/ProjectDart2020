#ifndef IDCIPTEVAL_H
#define IDCIPTEVAL_H
#include <qobject.h>
struct DCPlayer;
struct DCMeta;
struct DCInput;
class IDCIptEval : public QObject
{
    Q_OBJECT
public:
    virtual void eval(DCInput &input) = 0;
};
#endif // IPOINTVALIDATOR_H
