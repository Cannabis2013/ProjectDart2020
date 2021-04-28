#ifndef IDARTSJSONEXTRACTOR_H
#define IDARTSJSONEXTRACTOR_H
template<typename TJsonFormat,typename TPointModelInterface, typename TScoreModelInterface>
class IDartsInputJsonExtractor
{
public:

    virtual TPointModelInterface* extractDartsPointFromJson(const TJsonFormat&) = 0;
    virtual TScoreModelInterface* extractDartsScoreFromJson(const TJsonFormat&) = 0;
};

#endif // IDARTSJSONEXTRACTOR_H
