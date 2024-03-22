#ifndef DCFINISHBUILDER_H
#define DCFINISHBUILDER_H

#include "dartscreatefinishes.h"
#include "src/Finishes/idartsfinishes.h"

class DartsFinishes : public IDartsFinishes {
public:
        DartsFinishes();
        QString suggestTargetRow(const int& remainingScore, const int& turnIndex) const override;

private:
        QString getTargetRow(const int& turnIndex, const int& remainingScore) const;

        FinishesTypes::TargetRows* _finishes;

        DartsCreateFinishes* _constructRow = new DartsCreateFinishes();
};
#endif // SCORECONTROLLER_H

