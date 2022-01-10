#ifndef IDCFINISHBUILDER_H
#define IDCFINISHBUILDER_H
class QString;
class IDCFinishBuilder
{
public:
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const = 0;
};

#endif // ILOGISTICMANAGER_H
