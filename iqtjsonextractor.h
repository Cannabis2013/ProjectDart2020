#ifndef IQTJSONEXTRACTOR_H
#define IQTJSONEXTRACTOR_H

#include "ijsonextractor.h"
#include <quuid.h>
class IQtJsonExtractor : public IJsonExtractor<QByteArray,QUuid,QString>
{
};

#endif // IQTJSONEXTRACTOR_H
