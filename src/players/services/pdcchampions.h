#ifndef PDCCHAMPIONS_H
#define PDCCHAMPIONS_H

#include "iplayergenerator.h"

class QRandomGenerator;

class PdcChampions : public IPlayerGenerator {
public:
        PdcChampions();
        QList<DartsPlayer> generate(const int &count = 2) override;

private:
        QList<DartsPlayer> _available;
};

#endif // PDCCHAMPIONS_H
