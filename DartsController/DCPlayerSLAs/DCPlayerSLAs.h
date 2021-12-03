#ifndef DCPLAYERSLAS_H
#define DCPLAYERSLAS_H
#include "IDCPlayerCtx.h"
class DCPlayerSLAs
{
public:
    IDCPlayerCtx *playersContext() const
    {
        return _playerController;
    }
    void setPlayerContext(IDCPlayerCtx *controller)
    {
        _playerController = controller;
    }
private:
    IDCPlayerCtx *_playerController = nullptr;
};
#endif // DCPLAYERSLAS_H
