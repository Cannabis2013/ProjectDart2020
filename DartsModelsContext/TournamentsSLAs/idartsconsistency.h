#ifndef IDARTSCONSISTENCY_H
#define IDARTSCONSISTENCY_H

class DartsModelsServices;
class QUuid;

class IDartsConsistency
{
public:
    virtual bool verify(const QUuid &tournamentID, const DartsModelsServices *services) const = 0;
};
#endif // IDARTSCONSISTENCY_H
