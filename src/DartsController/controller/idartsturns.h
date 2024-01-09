#ifndef IDARTSTURNS_H
#define IDARTSTURNS_H

class IDartsEvaluator;

class IDartsTurns {
public:
        virtual void init(IDartsEvaluator* evaluator) = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
};

#endif // IDARTSTURNS_H
