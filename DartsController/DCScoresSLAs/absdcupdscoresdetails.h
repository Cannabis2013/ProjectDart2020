#ifndef ABSDCUPDSCORESDETAILS_H
#define ABSDCUPDSCORESDETAILS_H
#include <PlayerStatsSLAs/idcstatscontext.h>
class AbsDCPlayersCtx;
class AbsDCUpdScoresDetails
{
public:
    AbsDCUpdScoresDetails(IDCStatsContext *statsCtx, AbsDCPlayersCtx  *scoresCtx):
        _statsCtx(statsCtx),_playersCtx(scoresCtx){}
    virtual void update(const DCInput &ipt) = 0;
    AbsDCPlayersCtx *scoresCtx() const {return _playersCtx;}
    IDCStatsContext *statsCtx() const {return _statsCtx;}
private:
    IDCStatsContext *_statsCtx;
    AbsDCPlayersCtx  *_playersCtx;
};
#endif // ABSTRACTDCUPDATESCOREDETAILS_H
