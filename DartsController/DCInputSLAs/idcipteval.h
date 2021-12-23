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
    virtual void eval(DCInput &input, const int &scoreCand, DCMeta &meta, const DCPlayer &player, const int &winnerStatus) = 0;
};
#endif // IPOINTVALIDATOR_H
