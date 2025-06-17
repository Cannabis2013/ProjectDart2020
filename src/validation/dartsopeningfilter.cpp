#include "dartsopeningfilter.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/inputsvalidationpersistence.h"

DartsOpeningFilter::DartsOpeningFilter(ServiceCollection *services):
    _services(services){
    _persistence = new InputsValidationPersistence("allowances.dat");
}

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
    _allowances = _persistence->readAllowances();
    _openingModifier = _persistence->readModifier();
}

void DartsOpeningFilter::saveState() {
    _persistence->save(_allowances,_openingModifier);
}

void DartsOpeningFilter::reset() {
    auto names = _allowances.keys();
    for (const auto& name : std::as_const(names))
        _allowances.insert(name,false);
}

bool DartsOpeningFilter::isValid(const int &point, const QString &mod) const
{
    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->players->all().at(playerIndex).name();
    if(_allowances.value(name))
        return true;
    return point == 20 && mod == _openingModifier;
}
