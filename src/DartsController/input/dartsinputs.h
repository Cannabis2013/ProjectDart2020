#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "IDartsInputs.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/inputsio.h"
#include "src/DartsController/players/idartsplayers.h"

#include <QList>

class DartsInputs : public IDartsInputs {
public:
        DartsInputs(IDartsIndexes* indexes, IDartsPlayers* players);
        virtual void init() override { _inputs = QList<Input>(); }
        virtual void setInputs(const QList<Input>& inputs) override { _inputs = inputs; }
        void initFromFile() override;
        const QList<Input>& inputs() const override { return _inputs; }
        QList<Input> inputs(const QString& playerName, const int& throwIndex) const override;
        virtual void remove(const std::function<bool(const Input&)>& predicate) override;
        bool saveState() override { return _inputsIO->toFile(_inputs); }
        Input save(Input input) override;

private:
        QList<Input> _inputs;

        // Services
        IDartsIndexes* _indexes;
        IDartsPlayers* _players;
        InputsIO* _inputsIO;
};

#endif // DARTINPUTS_H
