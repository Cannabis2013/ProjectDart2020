#ifndef DARTSBUILDER_H
#define DARTSBUILDER_H

#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h>

class DartsTournament;
template<typename T> class IModel;

#define DARTS_GAMEMODE 0x1

class DartsBuilder : public IDartsBuilder<IModel<QUuid>>
{
public:
    virtual Model *createModel(const QByteArray &json) const override;
    virtual Model *createInitial(std::function<void(Model*)> initializer) const override;
private:
    DartsTournament *create() const;
    QJsonObject fromByteArray(const QByteArray &json) const;
    const QJsonArray toJsonArray(const QByteArray &json) const;
    const QVector<IModel<QUuid>*> toModels(const QJsonArray &arr) const;
    DartsTournament* toModel(const QJsonObject& obj) const;
    void setTournamentPlayerDetails(DartsTournament *tournament, const QJsonObject &obj) const;
    QUuid toId(const QJsonObject &obj, const QString &key, const QString &defaultvalue = "") const;
};
#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
