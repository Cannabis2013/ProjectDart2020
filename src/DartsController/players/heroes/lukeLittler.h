#ifndef LUKELITTLER_H
#define LUKELITTLER_H

#include "src/DartsController/players/dartsplayer.h"

class LukeLittler : public DartsPlayer {
public:
        LukeLittler()
        {
                _winnerImageUrl = "qrc:/pictures/Ressources/Pictures/lukeLittler.gif";
                _name = "Luke Littler";
        }
};

#endif // LUKELITTLER_H
