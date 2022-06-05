#ifndef DSCINPUTADDER_H
#define DSCINPUTADDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <DartsController/Inputs/idcinputadder.h>

class DSCInputAdder : public IDCInputAdder
{
public:
    DCInput add(DCInput &input, const DCPlayer &player, const DCMeta &meta, const DCIndex &index) const override;
};
#endif // DARTSSCOREBUILDERSERVICE_H
