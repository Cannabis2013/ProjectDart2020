#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
class AbsDCCalcScore;
class DCPlayer;
class DCIndex;
class QByteArray;
class DCInput;
class AbsDCPlayersCtx;
class IDCIdxCtrl;
class AbstractDCInputBuilder
{
public:
    typedef IDCIdxCtrl IndexCtrl;
    typedef AbsDCPlayersCtx PlayersContext;
    virtual DCInput create(const QByteArray &json, const DCIndex &idx, const DCPlayer &player) const = 0;
    virtual DCInput create(const int &remScore, const DCPlayer &player) const = 0;
protected:
    AbstractDCInputBuilder(AbsDCCalcScore *scoreCalc):
        _inputScoreContext(scoreCalc){}
    AbsDCCalcScore *inputScoreCtx() const {return _inputScoreContext;}
private:
    AbsDCCalcScore *_inputScoreContext;
};
#endif // IDPCMODELCREATOR_H
