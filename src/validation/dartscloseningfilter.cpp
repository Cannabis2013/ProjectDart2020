#include "dartscloseningfilter.h"
#include "src/FileIO/filejsonio.h"
#include "src/players/idartsplayers.h"
#include "src/scores/idartsremainings.h"
#include "src/servicecollection.h"
#include "src/turns/dartsturnindex.h"
#include "src/turns/idartsindexes.h"

typedef QList<InputCandidate> Candidates;

DartsCloseningFilter::DartsCloseningFilter(ServiceCollection *services)
  : _services(services)
{}

void DartsCloseningFilter::init(bool enabled, const QString &mod)
{
    _enabled = enabled;
    _mod = mod;
}

const Candidates DartsCloseningFilter::filter(const Candidates &inputs)
{
    if (!_enabled)
        return inputs;

    Candidates accepted;

    auto playerIndex = _services->indexes->index().playerIndex();
    auto playerName = _services->players->all().at(playerIndex);
    auto remaining = _services->scores->fromPlayerName(playerName);

    for (const auto &input : inputs) {
        auto score = _services->scores->inputValue(input.input());
        remaining -= score;
        accepted << input;
        if (remaining == 0 && (input.mod() == _mod || input.point() == 50))
            return accepted;
        else if (remaining <= 1 && _mod == "D")
            return Candidates();
    }

  return accepted;
}

void DartsCloseningFilter::initFromFile() {
    FileJsonIO reader("closure.dat");

    auto jsonObj = reader.readAsJson().object();

    _enabled = jsonObj.value("enabled").toBool();
}

void DartsCloseningFilter::saveState() {
    FileJsonIO writer("closure.dat");

    QJsonObject jsonObj;

    jsonObj.insert("enabled", _enabled);

    writer.write(jsonObj);
}
