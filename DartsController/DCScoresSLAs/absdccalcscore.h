#ifndef ABSDCCALCSCORE_H
#define ABSDCCALCSCORE_H
struct DCInput;
class AbsDCPlayersCtx;
class IDCIdxCtrl;
class AbsDCCalcScore
{
public:
    AbsDCCalcScore(IDCIdxCtrl *indexController, AbsDCPlayersCtx *scoresContext):
        _idxCtrl(indexController),_scoresContext(scoresContext){}
    virtual int calc(DCInput &input) const = 0;
    virtual int calc(const int &scoreCandidate) const = 0;
    AbsDCPlayersCtx *scoresContext() const {return _scoresContext;}
    IDCIdxCtrl *idxCtrl() const {return _idxCtrl;}
private:
    IDCIdxCtrl *_idxCtrl;
    AbsDCPlayersCtx *_scoresContext;
};
#endif // ABSDCCALCSCORE_H
