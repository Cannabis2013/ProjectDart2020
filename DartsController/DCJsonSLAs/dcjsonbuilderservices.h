#ifndef DCJSONBUILDERSERVICES_H
#define DCJSONBUILDERSERVICES_H
struct DCPlayerStats;
struct DCIndex;
struct DCInput;
template<typename T>
class IDCModelJsonBuilder;
struct DCMeta;
struct DCTurnValues;
struct DCPlayer;
class DCJsonBuilderServices
{
public:
    IDCModelJsonBuilder<const DCMeta&> *metaJsonBuilder() const {return _metaJsonBuilder;}
    void setMetaJsonBuilder(IDCModelJsonBuilder<const DCMeta&> *builder) {_metaJsonBuilder = builder;}
    IDCModelJsonBuilder<DCInput> *inputJsonBuilder() const {return _inputJsonBuilder;}
    void setInputJsonBuilder(IDCModelJsonBuilder<DCInput> *newInputJsonBuilder) {_inputJsonBuilder = newInputJsonBuilder;}
    IDCModelJsonBuilder<DCIndex> *inputIndexesBuilder() const {return _inputIndexJsonBuilder;}
    void setIdxJsonBuilder(IDCModelJsonBuilder<DCIndex> *newIndexesJsonBuilder) {_inputIndexJsonBuilder = newIndexesJsonBuilder;}
    IDCModelJsonBuilder<const DCTurnValues&> *turnValuesJsonBuilder() const {return _turnValuesJsonBuilder;}
    void setTurnValuesJsonBuilder(IDCModelJsonBuilder<const DCTurnValues&> *newTurnValuesJsonBuilder) {_turnValuesJsonBuilder = newTurnValuesJsonBuilder;}
    IDCModelJsonBuilder<DCIndex> *reqIndexJsonBuilder() const {return _reqIndexJsonBuilder;}
    void setReqIdxJsonBuilder(IDCModelJsonBuilder<DCIndex> *newReqIndexJsonBuilder) {_reqIndexJsonBuilder = newReqIndexJsonBuilder;}
    IDCModelJsonBuilder<const DCPlayer&> *scoreModelJsonBuilder() const {return _scoreModelJsonBuilder;}
    void setScoreModelJsonBuilder(IDCModelJsonBuilder<const DCPlayer&> *newScoreModelJsonBuilder) {_scoreModelJsonBuilder = newScoreModelJsonBuilder;}
    IDCModelJsonBuilder<const DCPlayerStats&> *playerStatsJsonBuilder() const {return _playerStatsJsonBuilder;}
    void setPlayerStatsJsonBuilder(IDCModelJsonBuilder<const DCPlayerStats&> *newPlayerStatsJsonBuilder) {_playerStatsJsonBuilder = newPlayerStatsJsonBuilder;}
private:
    IDCModelJsonBuilder<const DCMeta&> *_metaJsonBuilder;
    IDCModelJsonBuilder<DCInput> *_inputJsonBuilder;
    IDCModelJsonBuilder<DCIndex> *_inputIndexJsonBuilder;
    IDCModelJsonBuilder<DCIndex> *_reqIndexJsonBuilder;
    IDCModelJsonBuilder<const DCTurnValues&> *_turnValuesJsonBuilder;
    IDCModelJsonBuilder<const DCPlayer&> *_scoreModelJsonBuilder;
    IDCModelJsonBuilder<const DCPlayerStats&> *_playerStatsJsonBuilder;
};
#endif // DCJSONBUILDERSERVICES_H
