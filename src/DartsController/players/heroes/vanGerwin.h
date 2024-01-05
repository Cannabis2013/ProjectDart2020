#ifndef VANGERWIN_H
#define VANGERWIN_H

#include "src/DartsController/players/dartsplayer.h"

class VanGerwin : public DartsPlayer {
public:
        VanGerwin()
        {
                _winnerImageUrl = "qrc:/pictures/Ressources/Pictures/VanGerwin.gif";
                _name = "Van Gerwin";
        }
};

#endif // VANGERWIN_H
