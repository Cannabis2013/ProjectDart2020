#include "pdcchampions.h"
#include <QList>
#include <qrandom.h>

PdcChampions::PdcChampions()
{
    _available = std::initializer_list<DartsPlayer>{
        {"Van Gerwen", "qrc:/pictures/Ressources/Pictures/VanGerwin.gif", "NL"},
        {"Peter Wright", "qrc:/pictures/Ressources/Pictures/SnakeBite.png", "EN"},
        {"Luke Littler", "qrc:/pictures/Ressources/Pictures/lukeLittler.gif", "EN"},
        {"Gerwin Price", "qrc:/pictures/Ressources/Pictures/gerwinPrice.gif", "EN"},
        {"Luke Humphries", "qrc:/pictures/Ressources/Pictures/lukeHumphries.gif", "EN"},
        {"Benjamin Drue Reus", "qrc:/pictures/Ressources/Pictures/benjamin.jpeg", "DK"}
    };
}

QList<DartsPlayer> PdcChampions::generate(const int &count)
{
    QList<DartsPlayer> list;
    DartsPlayer player;
    QRandomGenerator rand(QTime::currentTime().msec());
    for (int i = 0; i < count; ++i){
        auto size = _available.size();
        auto index = rand.bounded(size);
        player = _available.takeAt(index);
        list << player;
    }
    return list;
}
