#include "dartscloseningfilter.h"
#include "src/FileIO/filejsonio.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/services/idartsremainings.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

typedef QList<InputCandidate> Candidates;

DartsCloseningFilter::DartsCloseningFilter(ServiceCollection *services)
  : _services(services)
{}

void DartsCloseningFilter::init(bool enabled)
{
    _enabled = enabled;
}

const Candidates DartsCloseningFilter::filter(const Candidates &inputs)
{
    if (!_enabled)
        return inputs;

    Candidates accepted;

    auto playerIndex = _services->indexes->index().playerIndex();
    auto playerName = _services->playerFetcher->names().at(playerIndex);
    auto remaining = _services->scores->remaining(playerName);

    for (const auto &input : inputs) {
        auto score = _services->scores->calculateRemaining(input.input());
        remaining -= score;
        accepted << input;
        if (remaining == 0 && (input.mod() == "D" || input.point() == 50))
            return accepted;
        else if (remaining < 0)
            return Candidates();
    }

  return accepted;
}

void DartsCloseningFilter::evaluateWinnerCondition() {
    auto players = &_services->players->all();

    for (auto &player : *players) {
        auto name = player.name();
        auto remaining = _services->scores->remaining(name);
        auto isWinner = remaining <= 0;
        player.setWinner(isWinner);
    }
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
