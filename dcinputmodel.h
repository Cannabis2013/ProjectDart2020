#ifndef DCINPUTMODEL_H
#define DCINPUTMODEL_H

#include <idcinputmodel.h>

namespace DCContext {
    class DCInputModel : public IDCInputModel
    {
    public:
        virtual int point() const override
        {
            return _point;
        }
        virtual int modKeyCode() const override
        {
            return _modKeyCode;
        }
        virtual int score() const override
        {
            return _score;
        }
    private:
        int _point, _modKeyCode, _score;
    };
}
#endif // DCINPUTMODEL_H
