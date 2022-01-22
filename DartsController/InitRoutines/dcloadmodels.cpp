#include "dcloadmodels.h"
#include "SLAs/absdartsctx.h"
#include "DCMetaSLAs/idcmetabuilder.h"
#include "Models/dcmeta.h"
#include <ModelBuilderSLAs/idcmodelbuilder.h>
#include "Models/dcinput.h"
#include "Models/dcplayer.h"
#include "ModelsConverterSLAs/idcmodelsconverter.h"
#include "qjsonobject.h"

DCLoadModels::DCLoadModels(MetaBuilder *metaBuilder, ConvertPlayer *convertPlayer, ConvertPlayers *convertPlayers,
                           ConvertInput *convertInput, ConvertInputs *convertInputs):
    _metaBuilder(metaBuilder),_convertPlayer(convertPlayer),_convertPlayers(convertPlayers),_convertInput(convertInput),
    _convertInputs(convertInputs){}

void DCLoadModels::load(const QUuid &tournamentId, AbsDartsCtx *ctx)
{
    auto tnmtBa = ctx->tournament(tournamentId);
    _meta = _metaBuilder->create(tnmtBa);
    _players = _convertPlayers->convert(tnmtBa,_convertPlayer);
    _inputs = _convertInputs->convert(ctx->inputs(tournamentId),_convertInput);
}

const DCMeta &DCLoadModels::meta() const
{
    return _meta;
}

const DCLoadModels::Players &DCLoadModels::players() const
{
    return _players;
}

const DCLoadModels::Inputs &DCLoadModels::inputs() const
{
    return _inputs;
}
