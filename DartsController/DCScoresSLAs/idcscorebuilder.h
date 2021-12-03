#ifndef IDCSCOREBUILDER_H
#define IDCSCOREBUILDER_H
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include <qstringlist.h>
#include <qvector.h>
class IDCScoreBuilder
{
public:
    struct Player
    {
        QString name;
        int score;
    };
    typedef QVector<Player> Players;
    virtual QVector<DCScoreModel> createScores(const QStringList &names, const int &initialScore) const = 0;
};
#endif // IDCSCOREBUILDER_H
