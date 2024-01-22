#include "pdcchampions.h"
#include <QList>
#include <qrandom.h>

PdcChampions::PdcChampions()
{
        _available = std::initializer_list<DartsPlayer> {
                { "Van Gerwin", "qrc:/pictures/Ressources/Pictures/VanGerwin.gif" },
                { "Peter Wright", "qrc:/pictures/Ressources/Pictures/SnakeBite.png" },
                { "Luke Littler", "qrc:/pictures/Ressources/Pictures/lukeLittler.gif" },
                { "Gerwin Price", "qrc:/pictures/Ressources/Pictures/gerwinPrice.gif" },
                { "Snot Leif" }
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
