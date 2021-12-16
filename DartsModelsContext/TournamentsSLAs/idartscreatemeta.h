#ifndef IDARTSCREATEMETA_H
#define IDARTSCREATEMETA_H
class QUuid;
class QByteArray;
class DartsMetaModel;
class IDartsCreateMeta
{
public:
    virtual DartsMetaModel create(const QByteArray &json) const = 0;
    virtual DartsMetaModel create(const QUuid &tournament, const QUuid &player) const = 0;
};
#endif // IDARTSCREATEMETA_H
