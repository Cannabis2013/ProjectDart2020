#ifndef IINPUTMODELSCOUNTSERVICE_H
#define IINPUTMODELSCOUNTSERVICE_H

template<typename TInputModelsService, typename TUuid>
class IInputModelsCountService
{
public:
    typedef TInputModelsService ModelsService;
    typedef TUuid IdFormat;
    virtual int countInputModelsByTournamentId(const IdFormat& tournamentId, const ModelsService* service) const = 0;

};

#endif // IINPUTMODELSCOUNTSERVICE_H
