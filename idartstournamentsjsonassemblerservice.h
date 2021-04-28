#ifndef IDARTSTOURNAMENTJSONASSEMBLER_H
#define IDARTSTOURNAMENTJSONASSEMBLER_H


template<typename TJsonArray, typename TBaseModels>
class IDartsTournamentsJsonAssemblerService
{
public:
    virtual TJsonArray assembleDartsTournamentsFromModels(const TBaseModels&) = 0;
};

#endif // IDARTSTOURNAMENTJSONASSEMBLER_H
