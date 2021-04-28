#ifndef DARTSINPUTJSONEXTRACTOR_H
#define DARTSINPUTJSONEXTRACTOR_H

#include "idartsinputjsonextractor.h"
#include "dartspointinput.h"
#include "dartsscoreinput.h"
#include "qjsonvalue.h"
#include "qjsonobject.h"



class DartsInputJsonExtractor : public IDartsInputJsonExtractor<QJsonValue,IModel<QUuid>,IModel<QUuid>>
{
public:

    // IDartsInputJsonExtractor interface
public:
    IModel<QUuid> *extractDartsPointFromJson(const QJsonValue &jsonValue);
    IModel<QUuid> *extractDartsScoreFromJson(const QJsonValue &);
};

#endif // DARTSINPUTJSONEXTRACTOR_H
