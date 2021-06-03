#ifndef IGETINPUTMODELSSERVICE_H
#define IGETINPUTMODELSSERVICE_H

#include <qvector.h>

template <typename TInputModelInterface,typename TDbServiceInterface, typename TUuid>
class IGetInputModelsService
{
public:
    typedef TInputModelInterface InputModel;
    typedef TDbServiceInterface DbServiceInterface;
    typedef TUuid IdFormat;
    typedef QVector<const InputModel*> InputModels;
    // Pure methods
    virtual InputModels inputModelsByTournamentId(const IdFormat& tournamentId,
                                                  const DbServiceInterface* dbService) const = 0;
    virtual InputModels inputModelsByHint(const IdFormat& tournamentId, const int& hint,
                                          const DbServiceInterface* dbService) const = 0;

};

#endif // IGETINPUTMODELSSERVICE_H
