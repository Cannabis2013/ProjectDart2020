#ifndef ICREATEMODEL_H
#define ICREATEMODEL_H

template<typename TPlayerModel, typename TJson>
class ICreateModel
{
public:
    virtual const TPlayerModel *createPlayerModel(const TJson &json) const = 0;
};

#endif // IPLAYERMODELBUILDER_H
