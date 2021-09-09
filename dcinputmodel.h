#ifndef DCINPUTMODEL_H
#define DCINPUTMODEL_H

#include <idcinputmodel.h>

namespace DCContext {
    class DCInputModel : public IDCInputModel
    {
    public:
        int point() const override
        {
            return _point;
        }
        void setPoint(const int &value)
        {
            _point = value;
        }
        int modKeyCode() const override
        {
            return _modKeyCode;
        }
        void setModKeyCode(const int &value)
        {
            _modKeyCode = value;
        }
        int score() const override
        {
            return _score;
        }
        void setScore(const int &value)
        {
            _score = value;
        }
    private:
        int _point, _modKeyCode, _score;
    };
}
#endif // DCINPUTMODEL_H
