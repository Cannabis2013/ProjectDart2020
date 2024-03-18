#ifndef PDCCHAMPIONS_H
#define PDCCHAMPIONS_H

#include "iplayergenerator.h"

class QRandomGenerator;

class PdcChampions : public IPlayerGenerator {
public:
        PdcChampions();
        QList<DartsPlayer> generate() override;

private:
        QList<DartsPlayer> takeRandoms(QList<DartsPlayer>& available, const int& count);
        DartsPlayer takeRandom(QList<DartsPlayer>& available, QRandomGenerator& rand);

        int _count = 2;
        QList<DartsPlayer> _available;
};

#endif // PDCCHAMPIONS_H
