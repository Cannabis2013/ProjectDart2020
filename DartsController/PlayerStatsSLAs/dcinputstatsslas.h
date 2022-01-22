#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
class IDCSetIptStats;
class IDCStatistics;
class PlayerStatsSLAs
{
public:
    IDCStatistics *statistics() const {return _statsCtx;}
    void setStatistics(IDCStatistics *builder) {_statsCtx = builder;}
    IDCSetIptStats *updateInputStats() const {return _setInputStats;}
    void setUpdateInputStats(IDCSetIptStats *service) {_setInputStats = service;}
private:
    IDCSetIptStats *_setInputStats;
    IDCStatistics *_statsCtx;
};
#endif // DCINPUTSTATSSLAS_H
