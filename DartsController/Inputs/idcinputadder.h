#ifndef IDCINPUTADDER_H
#define IDCINPUTADDER_H
class QByteArray;
class QJsonObject;
struct DCMeta;
struct DCPlayer;
struct DCIndex;
struct DCInput;
class IDCInputAdder
{
public:
    virtual DCInput add(DCInput &input, const DCPlayer &player, const DCMeta &meta, const DCIndex &index) const = 0;
};
#endif // IDPCMODELCREATOR_H
