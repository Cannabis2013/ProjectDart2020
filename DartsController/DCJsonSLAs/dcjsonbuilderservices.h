#ifndef DCJSONBUILDERSERVICES_H
#define DCJSONBUILDERSERVICES_H
#include "DartsController/DCMetaServices/dcmeta.h"
#include "idcmodeljsonbuilder.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/PlayerStatsSLAs/dcplayerstat.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
#include "DartsController/DCInputSLAs/dciptvals.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
class DCJsonBuilderServices
{
public:
    IDCModelJsonBuilder<const DCMeta&> *metaJsonBuilder() const
    {
        return _metaJsonBuilder;
    }
    void setMetaJsonBuilder(IDCModelJsonBuilder<const DCMeta&> *builder)
    {
        _metaJsonBuilder = builder;
    }
    IDCModelJsonBuilder<DCIptVals> *inputJsonBuilder() const
    {
        return _inputJsonBuilder;
    }
    void setInputJsonBuilder(IDCModelJsonBuilder<DCIptVals> *newInputJsonBuilder)
    {
        _inputJsonBuilder = newInputJsonBuilder;
    }
    IDCModelJsonBuilder<DCIndex> *inputIndexesBuilder() const
    {
        return _inputIndexJsonBuilder;
    }
    void setIdxJsonBuilder(IDCModelJsonBuilder<DCIndex> *newIndexesJsonBuilder)
    {
        _inputIndexJsonBuilder = newIndexesJsonBuilder;
    }
    IDCModelJsonBuilder<const DCTurnValues&> *turnValuesJsonBuilder() const
    {
        return _turnValuesJsonBuilder;
    }
    void setTurnValuesJsonBuilder(IDCModelJsonBuilder<const DCTurnValues&> *newTurnValuesJsonBuilder)
    {
        _turnValuesJsonBuilder = newTurnValuesJsonBuilder;
    }
    IDCModelJsonBuilder<DCIndex> *reqIndexJsonBuilder() const
    {
        return _reqIndexJsonBuilder;
    }
    void setReqIdxJsonBuilder(IDCModelJsonBuilder<DCIndex> *newReqIndexJsonBuilder)
    {
        _reqIndexJsonBuilder = newReqIndexJsonBuilder;
    }
    IDCModelJsonBuilder<const DCScoreModel&> *scoreModelJsonBuilder() const
    {
        return _scoreModelJsonBuilder;
    }
    void setScoreModelJsonBuilder(IDCModelJsonBuilder<const DCScoreModel&> *newScoreModelJsonBuilder)
    {
        _scoreModelJsonBuilder = newScoreModelJsonBuilder;
    }
    IDCModelJsonBuilder<const DCPlayerStat&> *playerStatsJsonBuilder() const
    {
        return _playerStatsJsonBuilder;
    }
    void setPlayerStatsJsonBuilder(IDCModelJsonBuilder<const DCPlayerStat&> *newPlayerStatsJsonBuilder)
    {
        _playerStatsJsonBuilder = newPlayerStatsJsonBuilder;
    }
private:
    IDCModelJsonBuilder<const DCMeta&> *_metaJsonBuilder;
    IDCModelJsonBuilder<DCIptVals> *_inputJsonBuilder;
    IDCModelJsonBuilder<DCIndex> *_inputIndexJsonBuilder;
    IDCModelJsonBuilder<DCIndex> *_reqIndexJsonBuilder;
    IDCModelJsonBuilder<const DCTurnValues&> *_turnValuesJsonBuilder;
    IDCModelJsonBuilder<const DCScoreModel&> *_scoreModelJsonBuilder;
    IDCModelJsonBuilder<const DCPlayerStat&> *_playerStatsJsonBuilder;
};
#endif // DCJSONBUILDERSERVICES_H
