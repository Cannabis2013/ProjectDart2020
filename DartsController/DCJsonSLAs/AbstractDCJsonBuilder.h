#ifndef ABSTRACTDCJSONBUILDER_H
#define ABSTRACTDCJSONBUILDER_H

#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCMetaServices/dcmetainfo.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCIndexServices/dcindexes.h"
#include "idcmodeljsonbuilder.h"
#include "DartsController/DCInputStatsSLAs/dcinputstats.h"

class AbstractDCJsonBuilder
{
public:
    virtual QByteArray json(const DCMetaInfo &metaInfo) const = 0;
    virtual QByteArray json(const QVector<DCInput> &inputs) const = 0;
    virtual QByteArray json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCIndexes &indexes, const DCInputStat &stats, const DCMetaInfo &metaInfo  = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCIndexes &indexes, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCIndexes &indexes, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
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
    IDCModelJsonBuilder<DCIndexes> *indexesJsonBuilder() const
    {
        return _indexesJsonBuilder;
    }
    void setIndexesJsonBuilder(IDCModelJsonBuilder<DCIndexes> *newIndexesJsonBuilder)
    {
        _indexesJsonBuilder = newIndexesJsonBuilder;
    }

    IDCModelJsonBuilder<DCTurnValues> *turnValuesJsonBuilder() const
    {
        return _turnValuesJsonBuilder;
    }
    void setTurnValuesJsonBuilder(IDCModelJsonBuilder<DCTurnValues> *newTurnValuesJsonBuilder)
    {
        _turnValuesJsonBuilder = newTurnValuesJsonBuilder;
    }

    IDCModelJsonBuilder<DCInputStat> *inputStatJsonBuilder() const
    {
        return _inputStatJsonBuilder;
    }
    void setInputStatJsonBuilder(IDCModelJsonBuilder<DCInputStat> *newInputStatJsonBuilder)
    {
        _inputStatJsonBuilder = newInputStatJsonBuilder;
    }
protected:
    IDCModelJsonBuilder<DCMetaInfo> *_metaJsonBuilder;
    IDCModelJsonBuilder<DCInput> *_inputJsonBuilder;
    IDCModelJsonBuilder<DCIndexes> *_indexesJsonBuilder;
    IDCModelJsonBuilder<DCTurnValues> *_turnValuesJsonBuilder;
    IDCModelJsonBuilder<DCInputStat> *_inputStatJsonBuilder;
};
#endif // IDCJSONBUILDER_H
