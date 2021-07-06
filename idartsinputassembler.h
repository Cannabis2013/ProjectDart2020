#ifndef IDARTSPOINTASSEMBLER_H
#define IDARTSPOINTASSEMBLER_H

template<typename TJsonFormat, typename TBaseModelInterface>
class IDartsInputAssembler
{
public:
    virtual TJsonFormat createDartsPointJson(const TBaseModelInterface&) = 0;
    virtual TJsonFormat createDartsScoreJson(const TBaseModelInterface&) = 0;
};

#endif // IDARTSPOINTASSEMBLER_H
