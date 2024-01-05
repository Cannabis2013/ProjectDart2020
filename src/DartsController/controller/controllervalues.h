#ifndef CONTROLLERVALUES_H
#define CONTROLLERVALUES_H

#include "src/DartsController/players/dartsplayer.h"

class ControllerValues {
public:
        ControllerValues(const QByteArray& json);
        int playersCount() const;

        int initialScore() const;

        int mode() const;

private:
        int _playersCount;
        int _initialScore;
        int _mode;
};

#endif // CONTROLLERVALUES_H
