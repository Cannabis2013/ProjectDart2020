#ifndef IDCUPDATEPLAYERSTATS_H
#define IDCUPDATEPLAYERSTATS_H
class IDCStatistics;
class DCInput;
class AbsDCPlayersCtx;
class IDCUpdatePlayerStats
{
public:
    virtual void update(const DCInput &ipt, IDCStatistics *_statsCtx, AbsDCPlayersCtx  *_playersCtx) = 0;
};
#endif // ABSTRACTDCUPDATESCOREDETAILS_H
