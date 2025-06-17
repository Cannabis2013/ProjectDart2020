#include "dartsopeningfilter.h"
#include "src/FileIO/filejsonio.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

DartsOpeningFilter::DartsOpeningFilter(ServiceCollection *services):
    _services(services){}

void DartsOpeningFilter::init(const QList<QString> &names, bool withOpening, const QString &openingMod)
{
    _openingModifier = openingMod;
    for (const auto& name : names)
        _allowances.insert(name,!withOpening);
}

void DartsOpeningFilter::update(const QString &name, bool allowed) {
    _allowances.insert(name,allowed);
}

QList<InputCandidate> DartsOpeningFilter::filter(const QList<InputCandidate> &inputs) {
    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->players->all().at(playerIndex).name();
    if(_allowances.value(name))
        return inputs;
    QList<InputCandidate> allowedCandidates;
    for (const auto &input : inputs) {
        if(input.point() == 20 && input.mod() == _openingModifier)
            _allowances.insert(name,true);
        if(_allowances.value(name))
            allowedCandidates << input;
    }
    return allowedCandidates;
}

void DartsOpeningFilter::initFromFile() {
    FileJsonIO reader("allowances.dat");
    auto jsonObject = reader.readAsJson().object();
    _openingModifier = jsonObject.value("openingModifier").toString("D");
    auto arr = jsonObject.value("allowances").toArray();
    QJsonObject obj;
    for (const auto& value : std::as_const(arr)) {
        obj = value.toObject();
        _allowances.insert(obj.value("key").toString(),obj.value("val").toBool());
    }
}

void DartsOpeningFilter::saveState() {
    FileJsonIO writer("allowances.dat");
    QJsonObject jsonObj;
    jsonObj.insert("openingModifier",_openingModifier);
    QJsonObject obj;
    QJsonArray arr;
    auto keys = _allowances.keys();
    for (const auto& key : std::as_const(keys)) {
        obj.insert("key",key);
        obj.insert("value",_allowances.value(key));
        arr << obj;
    }
    jsonObj.insert("allowances",arr);
    writer.writeFromObject(jsonObj);
}

void DartsOpeningFilter::reset() {
    auto names = _allowances.keys();
    for (const auto& name : std::as_const(names))
        _allowances.insert(name,false);
}
