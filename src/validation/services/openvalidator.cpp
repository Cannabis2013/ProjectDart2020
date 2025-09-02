#include "openvalidator.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/persistence/ivalidationopenpersistence.h"

OpenValidator::OpenValidator(ServiceCollection *services):
    _services(services){
}

void OpenValidator::init(bool withOpening, const QString &openingMod)
{
    _withOpen = withOpening;
    auto names = _services->playerFetcher->names();
    _openingModifier = openingMod;
    for (const auto& name : std::as_const(names))
        _allowances.insert(name,!_withOpen);
}

void OpenValidator::update(const QString &name, bool allowed) {
    if(_withOpen)
        _allowances.insert(name,allowed);
}

QList<InputCandidate> OpenValidator::filter(const QList<InputCandidate> &inputs) {
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

void OpenValidator::initFromFile() {
    _allowances = _services->openPersistence->readAllowances();
    _openingModifier = _services->openPersistence->readModifier();
}

void OpenValidator::saveState() {
    _services->openPersistence->save(_allowances,_openingModifier);
}

void OpenValidator::reset() {
    _allowances.clear();
    auto names = _services->playerFetcher->names();
    for (const auto& name : std::as_const(names))
        _allowances.insert(name,!_withOpen);
}

bool OpenValidator::isValid(const int &point, const QString &mod) const
{
    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->players->all().at(playerIndex).name();
    if(_allowances.value(name))
        return true;
    return point == 20 && mod == _openingModifier;
}
