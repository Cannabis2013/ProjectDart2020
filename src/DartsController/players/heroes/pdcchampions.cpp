#include "pdcchampions.h"
#include "src/DartsController/players/heroes/snakeBite.h"
#include "src/DartsController/players/heroes/vanGerwin.h"
#include <QList>
#include <qrandom.h>

PdcChampions::PdcChampions(const int& count)
{
        _available = std::initializer_list<DartsPlayer> {
                VanGerwin(),
                SnakeBite()
        };
        if (count < 0 || count >= _available.size())
                _count = 2;
        else
                _count = count;
}

QList<DartsPlayer> PdcChampions::generate()
{
        return takeRandoms(_available, _count);
}

QList<DartsPlayer> PdcChampions::takeRandoms(QList<DartsPlayer>& available, const int& count)
{
        QList<DartsPlayer> list;
        QRandomGenerator rand(QTime::currentTime().msec());
        while (!available.isEmpty())
                list << takeRandom(available, rand);
        return list;
}

DartsPlayer PdcChampions::takeRandom(QList<DartsPlayer>& available, QRandomGenerator& rand)
{
        auto size = available.size();
        auto index = rand.bounded(size);
        return available.takeAt(index);
}
