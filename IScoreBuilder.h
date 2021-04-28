#ifndef ISCOREBUILDER_H
#define ISCOREBUILDER_H

template <typename TBaseModel,
          typename TParameters,
          typename TOptions>
class IScoreBuilder
{
public:
    virtual TBaseModel* buildDartsPoint(const TParameters&, const TOptions&) = 0;
};

#endif // ISCOREBUILDER_H
