#ifndef IDARTSTOURNAMENTJSONEXTRACTORSERVICE_H
#define IDARTSTOURNAMENTJSONEXTRACTORSERVICE_H

template <typename TJsonFormat,typename TTournamentInterface>
class IDartsTournamentJsonExtractorService
{
public:
    virtual TTournamentInterface extractDartsTournamentFromJson(const TJsonFormat&) = 0;
};

#endif // IDARTSTOURNAMENTJSONEXTRACTORSERVICE_H
