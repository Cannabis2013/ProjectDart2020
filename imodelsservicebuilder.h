#ifndef ITOURNAMENTMODELSSERVICEASSEMBLER_H
#define ITOURNAMENTMODELSSERVICEASSEMBLER_H

template<typename TModelsServiceInterface>
class IModelsServiceBuilder
{
public:
    virtual TModelsServiceInterface* buildModelsService() const = 0;
};

#endif // ITOURNAMENTMODELSSERVICEASSEMBLER_H
