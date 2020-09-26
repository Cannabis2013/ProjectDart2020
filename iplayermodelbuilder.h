#ifndef IPLAYERMODELBUILDER_H
#define IPLAYERMODELBUILDER_H
template<class TPlayerModel, class TParameter, class TOptions>
class IPlayerModelBuilder
{
public:
    virtual TPlayerModel *buildPlayerModel(const TParameter &params, const TOptions &options) = 0;
};

#endif // IPLAYERMODELBUILDER_H
