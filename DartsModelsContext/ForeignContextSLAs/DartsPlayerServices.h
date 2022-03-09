#ifndef DARTSPLAYERSERVICES_H
#define DARTSPLAYERSERVICES_H
#include "IDartsConvertPlayer.h"
class DartsPlayerServices
{
public:
    IDartsConvertPlayer *playerConverter() const {return _convertPlayers;}
    void setPlayerConverter(IDartsConvertPlayer *service) {_convertPlayers = service;}
private:
    IDartsConvertPlayer *_convertPlayers;
};
#endif // DARTSPLAYERSERVICES_H
