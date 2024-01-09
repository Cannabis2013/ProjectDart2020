#ifndef IDARTSTURNS_H
#define IDARTSTURNS_H

class AbstractDartsEvaluator;

class IDartsTurns {
public:
        virtual void init(AbstractDartsEvaluator* evaluator) = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
};

#endif // IDARTSTURNS_H
