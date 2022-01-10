#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H
struct DCPlayer;
struct DCIndex;
class QByteArray;
struct DCInput;
class AbstractDCInputBuilder
{
public:
    virtual DCInput create(const QByteArray &json, const DCIndex &idx, const DCPlayer &player) const = 0;
    virtual DCInput create(const int &remScore, const DCPlayer &player) const = 0;
};
#endif // IDPCMODELCREATOR_H
