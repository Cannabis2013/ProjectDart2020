#ifndef IPLAYERGENERATOR_H
#define IPLAYERGENERATOR_H

#include "src/players/models/dartsplayer.h"

class IPlayerGenerator {
public:
        virtual QList<DartsPlayer> generate() = 0;
};

#endif // IPLAYERGENERATOR_H
