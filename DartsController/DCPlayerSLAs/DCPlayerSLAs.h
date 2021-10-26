#ifndef DCPLAYERSLAS_H
#define DCPLAYERSLAS_H

#include "IDCPlayerController.h"
#include "idcplayerbuilder.h"

class DCPlayerSLAs
{
public:
    IDCPlayerBuilder *playerBuilder() const
    {
        return _playerBuilderService;
    }
    void setPlayerBuilderService(IDCPlayerBuilder *service)
    {
        _playerBuilderService = service;
    }
    IDCPlayerController *playerController() const
    {
        return _playerController;
    }
    void setPlayerController(IDCPlayerController *controller)
    {
        _playerController = controller;
    }
private:
    IDCPlayerBuilder* _playerBuilderService;
    IDCPlayerController *_playerController = nullptr;
};
#endif // DCPLAYERSLAS_H
