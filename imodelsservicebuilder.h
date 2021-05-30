#ifndef ITOURNAMENTMODELSSERVICEASSEMBLER_H
#define ITOURNAMENTMODELSSERVICEASSEMBLER_H

template<typename TModelsServiceInterface>
class IModelsServiceBuilder
{
public:
    typedef TModelsServiceInterface ServiceInterface;
    virtual ServiceInterface* buildModelsService() const = 0;
};

#endif // ITOURNAMENTMODELSSERVICEASSEMBLER_H
