#ifndef ISCORESUPDATE_H
#define ISCORESUPDATE_H

class IScoresUpdate {
public:
        virtual void initPlayerScores(const int& initialScore) = 0;
        virtual void resetPlayerScores() = 0;
        virtual void updatePlayerScores() = 0;
};

#endif // ISCORESUPDATE_H
