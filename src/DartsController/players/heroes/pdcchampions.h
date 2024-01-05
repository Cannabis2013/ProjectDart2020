#ifndef PDCCHAMPIONS_H
#define PDCCHAMPIONS_H

#include <src/DartsController/players/dartsplayer.h>

class QRandomGenerator;

class PdcChampions {
public:
        PdcChampions(const int& count);
        QList<DartsPlayer> generate();

private:
        QList<DartsPlayer> takeRandoms(QList<DartsPlayer>& available, const int& count);
        DartsPlayer takeRandom(QList<DartsPlayer>& available, QRandomGenerator& rand);

        int _count;
        QList<DartsPlayer> _available;
};

#endif // PDCCHAMPIONS_H
