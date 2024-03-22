#ifndef DARTSEVALUATORS_H
#define DARTSEVALUATORS_H

#include "src/validation/abstractdartsevaluator.h"

class ServiceCollection;

class DartsEvaluators {
public:
        DartsEvaluators(ServiceCollection* services);

        AbstractDartsEvaluator* validator();
        AbstractDartsEvaluator* validator(const int& mode);

        bool readFromFile();
        void saveState();

private:
        AbstractDartsEvaluator* fromMode();

        // Services
        ServiceCollection* const _services;

        // Member variables
        int _mode = 0;
};

#endif // DARTSEVALUATORS_H
