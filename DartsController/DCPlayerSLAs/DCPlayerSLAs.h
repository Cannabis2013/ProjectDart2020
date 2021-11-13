#ifndef DCPLAYERSLAS_H
#define DCPLAYERSLAS_H
#include "IDCPlayerController.h"
class DCPlayerSLAs
{
public:
    IDCPlayerController *playerController() const
    {
        return _playerController;
    }
    void setPlayerController(IDCPlayerController *controller)
    {
        _playerController = controller;
    }
private:
    IDCPlayerController *_playerController = nullptr;
};
#endif // DCPLAYERSLAS_H
