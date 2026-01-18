#include "openvalidator.h"
#include "src/players/idartsplayers.h"
#include "src/servicecollection.h"
#include "src/turns/dartsturnindex.h"
#include "src/turns/idartsindexes.h"
#include "src/validation/jsonopenpersistence.h"

OpenValidator::OpenValidator(ServiceCollection *services)
  : _services(services)
{
    _persistence = new JsonOpenPersistence();
}

void OpenValidator::init(const QString &mod)
{
    _mod = mod;

    for (const auto &name : std::as_const(_services->players->all()))
        _allowances.insert(name, _mod.isEmpty());
}

void OpenValidator::update(const QString &name, bool allowed) {
    if (!_mod.isEmpty())
        _allowances.insert(name, allowed);
}

QList<InputCandidate> OpenValidator::filter(const QList<InputCandidate> &inputs) {
    if (_mod.isEmpty())
        return inputs;

    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->players->all().at(playerIndex);

    if (_allowances.value(name))
        return inputs;

    QList<InputCandidate> allowedCandidates;
    for (const auto &input : inputs) {
        if (input.point() == 20 && input.mod() == _mod)
            _allowances.insert(name, true);
        if (_allowances.value(name))
            allowedCandidates << input;
    }

    return allowedCandidates;
}

void OpenValidator::initFromFile() {
    _allowances = _persistence->readAllowances();
    _mod = _persistence->readModifier();
}

void OpenValidator::saveState() {
    _persistence->save(_allowances, _mod);
}

void OpenValidator::reset() {
    _allowances.clear();

    for (const auto &name : std::as_const(_services->players->all()))
        _allowances.insert(name, _mod.isEmpty());
}

bool OpenValidator::isValid(const int &point, const QString &mod) const
{
    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->players->all().at(playerIndex);

    if (_allowances.value(name))
        return true;

    return point == 20 && mod == _mod;
}
