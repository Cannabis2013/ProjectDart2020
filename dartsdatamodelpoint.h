#ifndef DARTSDATAMODELPOINT_H
#define DARTSDATAMODELPOINT_H

#include "idatamodelpoint.h"

namespace DartsDataModelsContext {
    class DartsDataModelPoint : public IDataModelPoint
    {
    public:
        int point() const override
        {
            return _point;
        }
        void setPoint(const int &point)
        {
            _point = point;
        }
        int score() const override
        {
            return _score;
        }
        void setScore(const int &score)
        {
            _score = score;
        }
    private:
        int _point;
        int _score;
    };
}

#endif // DARTSDATAMODELPOINT_H
