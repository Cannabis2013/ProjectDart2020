#ifndef GERWINPRICE_H
#define GERWINPRICE_H

#include "src/DartsController/players/dartsplayer.h"
class GerwinPrice : public DartsPlayer {
public:
        GerwinPrice()
        {
                _name = "Gerwin Price";
                _winnerImageUrl = "qrc:/pictures/Ressources/Pictures/gerwinPrice.gif";
        }
};

#endif // GERWINPRICE_H
