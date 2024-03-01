#ifndef DARTSSCORESREPORT_H
#define DARTSSCORESREPORT_H

#include "src/DartsController/scores/iscoresreport.h"

class IDartsScores;

class DartsScoresReport : public IScoresReport {
public:
        DartsScoresReport(IDartsScores* scores);
        QJsonObject report() const override;

private:
        IDartsScores* const _scores;
};

#endif // DARTSSCORESREPORT_H
