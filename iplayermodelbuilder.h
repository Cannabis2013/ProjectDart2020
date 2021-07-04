#ifndef IPLAYERMODELBUILDER_H
#define IPLAYERMODELBUILDER_H

template<typename TPlayerModel, typename TJson>
class IPlayerModelBuilder
{
public:
    typedef TPlayerModel Player;
    typedef TJson Json;
    virtual const Player *createPlayerModel(const Json &json) const = 0;
};

#endif // IPLAYERMODELBUILDER_H
