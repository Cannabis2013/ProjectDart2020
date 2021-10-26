#ifndef DCJSONBUILDERSERVICES_H
#define DCJSONBUILDERSERVICES_H
#include "DartsController/DCMetaServices/dcmetainfo.h"
#include "idcmodeljsonbuilder.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCIndexServices/dcindex.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/PlayerStatsSLAs/dcplayerstat.h"
class DCJsonBuilderServices
{
public:
    IDCModelJsonBuilder<DCMetaInfo> *metaJsonBuilder() const
    {
        return _metaJsonBuilder;
    }
    void setMetaJsonBuilder(IDCModelJsonBuilder<DCMetaInfo> *builder)
    {
        _metaJsonBuilder = builder;
    }
    IDCModelJsonBuilder<DCInput> *inputJsonBuilder() const
    {
        return _inputJsonBuilder;
    }
    void setInputJsonBuilder(IDCModelJsonBuilder<DCInput> *newInputJsonBuilder)
    {
        _inputJsonBuilder = newInputJsonBuilder;
    }
    IDCModelJsonBuilder<DCIndex> *inputIndexesBuilder() const
    {
        return _inputIndexJsonBuilder;
    }
    void setIndexesJsonBuilder(IDCModelJsonBuilder<DCIndex> *newIndexesJsonBuilder)
    {
        _inputIndexJsonBuilder = newIndexesJsonBuilder;
    }
    IDCModelJsonBuilder<DCTurnValues> *turnValuesJsonBuilder() const
    {
        return _turnValuesJsonBuilder;
    }
    void setTurnValuesJsonBuilder(IDCModelJsonBuilder<DCTurnValues> *newTurnValuesJsonBuilder)
    {
        _turnValuesJsonBuilder = newTurnValuesJsonBuilder;
    }
    IDCModelJsonBuilder<DCIndex> *reqIndexJsonBuilder() const
    {
        return _reqIndexJsonBuilder;
    }
    void setReqIndexJsonBuilder(IDCModelJsonBuilder<DCIndex> *newReqIndexJsonBuilder)
    {
        _reqIndexJsonBuilder = newReqIndexJsonBuilder;
    }
    IDCModelJsonBuilder<DCScoreModel> *scoreModelJsonBuilder() const
    {
        return _scoreModelJsonBuilder;
    }
    void setScoreModelJsonBuilder(IDCModelJsonBuilder<DCScoreModel> *newScoreModelJsonBuilder)
    {
        _scoreModelJsonBuilder = newScoreModelJsonBuilder;
    }
    IDCModelJsonBuilder<DCPlayerStat> *playerStatsJsonBuilder() const
    {
        return _playerStatsJsonBuilder;
    }
    void setPlayerStatsJsonBuilder(IDCModelJsonBuilder<DCPlayerStat> *newPlayerStatsJsonBuilder)
    {
        _playerStatsJsonBuilder = newPlayerStatsJsonBuilder;
    }
private:
    IDCModelJsonBuilder<DCMetaInfo> *_metaJsonBuilder;
    IDCModelJsonBuilder<DCInput> *_inputJsonBuilder;
    IDCModelJsonBuilder<DCIndex> *_inputIndexJsonBuilder;
    IDCModelJsonBuilder<DCIndex> *_reqIndexJsonBuilder;
    IDCModelJsonBuilder<DCTurnValues> *_turnValuesJsonBuilder;
    IDCModelJsonBuilder<DCScoreModel> *_scoreModelJsonBuilder;
    IDCModelJsonBuilder<DCPlayerStat> *_playerStatsJsonBuilder;
};
#endif // DCJSONBUILDERSERVICES_H
