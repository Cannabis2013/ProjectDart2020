#include "pdcchampions.h"
#include "src/DartsController/players/heroes/gerwinPrice.h"
#include "src/DartsController/players/heroes/lukeLittler.h"
#include "src/DartsController/players/heroes/snakeBite.h"
#include "src/DartsController/players/heroes/vanGerwin.h"
#include <QList>
#include <qrandom.h>

PdcChampions::PdcChampions()
{
        _available = std::initializer_list<DartsPlayer> {
                VanGerwin(),
                SnakeBite(),
                LukeLittler(),
                GerwinPrice()
        };
}

QList<DartsPlayer> PdcChampions::generate()
{
        return takeRandoms(_available, _count);
}

QList<DartsPlayer> PdcChampions::takeRandoms(QList<DartsPlayer>& available, const int& count)
{
        QList<DartsPlayer> list;
        QRandomGenerator rand(QTime::currentTime().msec());
        for (int i = 0; i < count; ++i)
                list << takeRandom(available, rand);
        return list;
}

DartsPlayer PdcChampions::takeRandom(QList<DartsPlayer>& available, QRandomGenerator& rand)
{
        auto size = available.size();
        auto index = rand.bounded(size);
        return available.takeAt(index);
}
