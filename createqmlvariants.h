#ifndef CREATEQMLVARIANTS_H
#define CREATEQMLVARIANTS_H

#include "iqmldatabuilder.h"
#include <QVariantList>

class CreateQMLVariants : public IQMLDataBuilder<QVector<QPair<int,int>>,QVariantList>
{
public:
    typedef QPair<int,int> PointInput;
    virtual QVariantList createData(const QVector<PointInput> &d) const override
    {
        QVariantList list;
        for (int i = 0;i < d.count();i++) {
            auto _d = d.value(i);
            QVariantMap map;
            map.insert("point",_d.first);
            map.insert("score",_d.second);
            list << map;
        }
        return list;
    }
};

#endif // QMLCONTEXTDATABUILDER_H
