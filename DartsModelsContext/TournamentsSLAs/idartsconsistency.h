#ifndef IDARTSCONSISTENCY_H
#define IDARTSCONSISTENCY_H
class QUuid;
class IDartsConsistency
{
public:
    virtual bool verify(const QUuid &tournamentID) const = 0;
};
#endif // IDARTSCONSISTENCY_H
