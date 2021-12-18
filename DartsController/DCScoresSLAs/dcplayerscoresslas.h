#ifndef DCPLAYERSCORESSLAS_H
#define DCPLAYERSCORESSLAS_H
#include "DCScoresSLAs/absdcplayersctx.h"
#include "DCScoresSLAs/absdccalcscore.h"
#include "absdcupdscoresdetails.h"
class DCPlayerScoresSLAs
{
public:
    AbsDCPlayersCtx *playersContext() const {return _scoresModels;}
    void setPlayersContext(AbsDCPlayersCtx *service) {_scoresModels = service;}
    AbsDCCalcScore *scoreCalc() const {return _calculateScore;}
    void setGetScoreFromInput(AbsDCCalcScore *service) {_calculateScore = service;}
    AbsDCUpdScoresDetails *updatePlayerDetails() const {return _updateScores;}
    void setUpdateScores(AbsDCUpdScoresDetails *newUpdateScores) {_updateScores = newUpdateScores;}
private:
    AbsDCPlayersCtx *_scoresModels;
    AbsDCCalcScore *_calculateScore;
    AbsDCUpdScoresDetails *_updateScores;
};
#endif // DSCSCORESERVICESPROVIDER_H
