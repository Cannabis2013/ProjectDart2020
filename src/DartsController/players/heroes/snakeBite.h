#ifndef SNAKEBITE_H
#define SNAKEBITE_H

#include "src/DartsController/players/dartsplayer.h"

class SnakeBite : public DartsPlayer {
public:
        SnakeBite()
        {
                _winnerImageUrl = "qrc:/pictures/Ressources/Pictures/SnakeBite.png";
                _name = "Peter Wright";
        }
};

#endif // SNAKEBITE_H
