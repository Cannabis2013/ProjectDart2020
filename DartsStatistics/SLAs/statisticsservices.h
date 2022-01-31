#ifndef STATISTICSSERVICES_H
#define STATISTICSSERVICES_H
#include "Players/playerservices.h"
#include "Inputs/inputservices.h"
class StatisticsServices
{
public:
    PlayerServices *playerServices() const {return _playerServices;}
    void setPlayerServices(PlayerServices *newPlayerServices) {_playerServices = newPlayerServices;}

    InputServices *inputServices() const {return _inputServices;}
    void setInputServices(InputServices *newInputServices) {_inputServices = newInputServices;}
private:
    PlayerServices *_playerServices;
    InputServices *_inputServices;
};
#endif // STATISTICSSERVICES_H
