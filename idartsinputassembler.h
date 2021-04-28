#ifndef IDARTSPOINTASSEMBLER_H
#define IDARTSPOINTASSEMBLER_H

template<typename TJsonFormat, typename TBaseModelInterface>
class IDartsInputAssembler
{
public:
    virtual TJsonFormat assembleDartsPointJson(const TBaseModelInterface&) = 0;
    virtual TJsonFormat assembleDartsScoreJson(const TBaseModelInterface&) = 0;
};

#endif // IDARTSPOINTASSEMBLER_H
