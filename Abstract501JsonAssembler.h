#ifndef ABSTRACT501JSONASSEMBLER_H
#define ABSTRACT501JSONASSEMBLER_H

template<typename TByteArray,
         typename TTournamentModelsContextInterface,
         typename TPlayerModelsContextInterface,
         typename TUuid>
class Abstract501JsonAssembler
{
public:
    virtual TByteArray assembleJsonFromMultiAttemptPoint(const TUuid&,
                                                         const TUuid&,
                                                         TTournamentModelsContextInterface*) = 0;
    virtual TByteArray assembleJsonFromSingleAttemptScore(const TUuid&,
                                                          const TUuid&,
                                                          TTournamentModelsContextInterface*,
                                                          TPlayerModelsContextInterface*) = 0;

};

#endif // ABSTRACT501JSONASSEMBLER_H
