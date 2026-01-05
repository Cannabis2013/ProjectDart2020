#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "idartsremainings.h"

#include <QString>

class ServiceCollection;
class Score;
class IScoresCalculator;
class IDartsInputs;
class IDartsPlayers;
class IDartsIndexes;

class DartsReminings : public IDartsRemainings{
public:
        DartsReminings(ServiceCollection *services,const QString& initialScoreFilename);
        void initFromStorage() override;
        int initialRemaining() const override;
        void setInitialRemaining(const int& initialScore) override;
        bool saveState() override;
        int fromPlayerName(const QString& name) const override;
        int inputValue(const DartsInput &input) const override;
        int calculateRemaining(const QList<DartsInput> &inputs) const override;

private:
        int readRemainingFromFile();

        // Member variables
        int _initialRemaining;
        QString _filename;
        ServiceCollection *_services;
};

#endif // DARTSCORES_H
