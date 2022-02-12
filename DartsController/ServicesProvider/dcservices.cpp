#include "dcservices.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "SLAs/absdartsctx.h"
#include "DCIndexSLAs/idcindexconverter.h"

void DCServices::setModelsContext(AbsDartsCtx *context) {_modelsContext = context;}
AbsDartsCtx *DCServices::modelsContext() {return _modelsContext;}
